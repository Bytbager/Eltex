#include "../server_type.h"

struct thread_attr threads[10];

/*Программа является слушающим сервером.
При запуске создаёт 10 потоков,
которые отправляют ответ клиентам.

На моём компьютере получается обслужить примерно 4000
клиентов, после этого возникает ошибка ENFILE в
программе клиента из-за превышения количества открытых дескрипторов*/
int main() {
    int serverFD, clientFD;
    in_addr_t servip;
    struct sockaddr_in servaddr, cliaddr, threadaddr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    pthread_t new_thread;
    pthread_attr_t attr;

    memset(threads, 0, 10 * sizeof(struct thread_attr));

    if (pthread_attr_init(&attr) != 0)
        errExit("pthreaad_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetachstate error!\n");

    /*Создаем 10 потоков, которые будут отвечать клиентам*/
    for (int i = 0; i < 10; i++) {
        threads[i].thread_readiness = THREAD_READY;
        if (pthread_create(&new_thread, &attr, (void *) server_thread_logic, (void *) i) != 0)
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
    
    /*При поступлении запроса от клиента, мы находим свободный поток
    и передаём ему дескриптор клиента*/
    while (1) {
        clientFD = accept(serverFD, (struct sockaddr *) &servaddr, &client_len);
        if (clientFD == -1)
            errExit("accept error!\n");
        for (int i = 0; i < 10; i++) {
            if (threads[i].thread_readiness == THREAD_READY) {
                threads[i].client_ds = clientFD;
                threads[i].thread_readiness = THREAD_BUSY;
                break;
            }
        }
    }

    return 0;
}