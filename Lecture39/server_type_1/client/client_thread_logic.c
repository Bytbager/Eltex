#include "../server_type.h"

/*Клиент создает сокет TCP, подключается к серверу
и ожидает от него ответ*/
void client_thread_logic(void *attr) {
    int serverFD;
    char msgbuf[32];
    memset(msgbuf, 0, 32);
    struct sockaddr_in servaddr;
    in_addr_t servip;
    
    /*Создаём сокет*/
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD == -1)
        errExit("socket error\n");
    
    /*Заполняем структуру сервера*/
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servip);
    servaddr.sin_addr.s_addr = servip;
    servaddr.sin_port = htons(SERVER_PORT);
    
    /*Подключаемся к серверу*/
    if (connect(serverFD, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("connect error\n");
    
    /*Получаем ответ и выводим на экран*/
    if (recv(serverFD, msgbuf, 32, 0) == -1)
        errExit("recv error\n");
    
    printf("%d - %s", (int) attr, msgbuf);

    /*Закрываем сокет и завершаем поток*/
    if (close(serverFD) == -1)
        errExit("close thread error\n");
    
    pthread_exit(NULL);
}