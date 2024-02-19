#include "../server_type.h"

int main() {
    int serverFD, clientFD;
    in_addr_t servip;
    struct sockaddr_in servaddr, cliaddr, threadaddr;
    socklen_t client_len;
    pthread_t new_thread;
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD == -1)
        errExit("socket error\n");
    memset(&servaddr, 0, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servip);
    servaddr.sin_addr.s_addr == servip;
    servaddr.sin_port = htons(SERVER_PORT);
    if (bind(serverFD, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("bind error\n");
    if (listen(serverFD, 5) == -1)
        errExit("listen error\n");
    for (int i = 0; ; i++) {
        client_len = sizeof(struct sockaddr_in);
        clientFD = accept(serverFD, (struct sockaddr *) &cliaddr, &client_len);
        if (clientFD == -1)
            errExit("accept error\n");
        memset(&threadaddr, 0, sizeof(struct sockaddr_in));
        threadaddr.sin_family = AF_INET;
        threadaddr.sin_addr.s_addr = servip;
        threadaddr.sin_port = htons(SERVER_PORT + i + 1);
        if (pthread_create(&new_thread, NULL, server_thread_logic, (void *) &threadaddr) != 0)
            errExit("pthread_create error\n");
        if (send(clientFD, &threadaddr, sizeof(struct sockaddr_in), 0) == -1)
            errExit("send new addr error\n");
    }
    if (close(serverFD) == -1)
        errExit("close serv error\n");
    return 0;
}