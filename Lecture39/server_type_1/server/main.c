#include "../server_type.h"

/*Программа является случающим сервером.
При подключении клиента, создаёт поток,
который отправляет ему ответ.

На моём компьютере получается обслужить примерно 5000
клиентов, после этого возникает ошибка ENFILE в
программе клиента из-за превышения количества открытых дескрипторов*/
int main() {
    int serverFD, clientFD;
    in_addr_t servip;
    struct sockaddr_in servaddr, cliaddr, threadaddr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    pthread_t new_thread;
    pthread_attr_t attr;

    if (pthread_attr_init(&attr) != 0)
        errExit("pthreaad_attr_init error!\n");
    if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0)
        errExit("pthread_attr_setdetachstate error!\n");

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
    
    /*При поступлении запроса от клиента, создаём
    поток, в который передаём сокет клиента*/
    while (1) {
        clientFD = accept(serverFD, (struct sockaddr *) &servaddr, &client_len);
        if (clientFD == -1)
            errExit("accept error!\n");
        if (pthread_create(&new_thread, &attr, (void *) server_thread_logic, (void *) clientFD) != 0)
            errExit("pthread_create error!\n");        
    }

    return 0;
}