#include "../server_type.h"

mqd_t mqds;

/*Программа является слушающим сервером.
При запуске создаёт 10 потоков,
которые отправляют ответ клиентам.

Дескриптор клиента отправляется в очередь POSIX,
из которой потоки забирают эти дескрипторы и отправляют
им ответы.

На моём компьютере получается обслужить примерно 7000
клиентов, после этого возникает ошибка ENFILE в
программе клиента из-за превышения количества открытых дескрипторов*/
int main() {
    int serverFD, clientFD;
    in_addr_t servip;
    struct sockaddr_in servaddr, cliaddr, threadaddr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    pthread_t new_thread;
    pthread_attr_t attr;
    struct mq_attr mqattr = {
        .mq_msgsize = 128,
        .mq_maxmsg = 10
    };

    int *msgptr = calloc(128, 1);
    if (msgptr == NULL)
        errExit("calloc error!\n");

    /*Открываем очередь*/
    mqds = mq_open("/mqueue", O_CREAT | O_RDWR, 0666, &mqattr);
    if (mqds == (mqd_t) -1)
        errExit(",q_open error!\n");

    if (pthread_attr_init(&attr) != 0)
        errExit("pthreaad_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetachstate error!\n");

    /*Создаем 10 потоков, которые будут отвечать клиентам*/
    for (int i = 0; i < 10; i++) {
        if (pthread_create(&new_thread, &attr, (void *) server_thread_logic, NULL) != 0)
            errExit("pthread_create error!\n");
    }

    /*Создаём сокет*/
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD == -1)
        errExit("socket error\n");
    
    /*Заполняем структуру сервера*/
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servip);
    servaddr.sin_addr.s_addr == servip;
    servaddr.sin_port = htons(SERVER_PORT);
    
    /*Привязываем адрес к сокету*/
    if (bind(serverFD, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("bind error\n");
    
    /*Задаём размер очереди клиентов*/
    if (listen(serverFD, 5) == -1)
        errExit("listen error\n");
    
    /*При поступлении запроса от клиента, мы отправляем его
    дескриптор в очередь, дальше какой-то из потоков его забирает 
    и отправляет ответ*/
    while (1) {
        memset(msgptr, 0, 128);
        clientFD = accept(serverFD, (struct sockaddr *) &servaddr, &client_len);
        if (clientFD == -1)
            errExit("accept error!\n");
        msgptr[0] = clientFD;
        if (mq_send(mqds, (char *) msgptr, 128, 1) == -1)
            errExit("send error!\n");
    }

    return 0;
}