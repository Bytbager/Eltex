#include "../server_type.h"

/*Программа создаёт клиента, исходя из полученного аргумента
командной строки:
./my_client tcp - создаёт клиента tcp
./my_client udp - создаёт клиента udp*/
int main(int argc, char **argv) {
    int sock_fd;
    struct sockaddr_in servaddr;
    char message[32];
    memset(message, 0, 32);
    strncat(message, "Hello, multiproto server!\n", strlen("Hello, multiproto server!\n") + 1);

    if (argc != 2) {
        fprintf(stderr, "Usage:\n"
        "%s tcp - makes tcp client\n"
        "%s udp - makes udp client\n", argv[0], argv[0]);
        return -1;
    }

    /*Если аргумент tcp:
    1. Создаём сокет sock_stream и заполняем структуру сервера
    2. Выполняем подключение с помощью connect
    3. Отправляем сообщение серверу и получаем ответ*/
    if (strcmp(argv[1], "tcp") == 0) {
        sock_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (sock_fd == -1)
            errExit("socket sock_stream error!\n");

        memset(&servaddr, 0, sizeof(struct sockaddr_in));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr.s_addr);
        servaddr.sin_port = htons(TCP_PORT);

        if (connect(sock_fd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
            errExit("connect error!\n");

        if (send(sock_fd, message, 32, 0) == -1)
            errExit("send error!\n");

        memset(message, 0, 32);
        if (recv(sock_fd, message, 32, 0) == -1)
            errExit("recv error!\n");

        printf("%s", message);

        if (close(sock_fd) == -1)
            errExit("close tcp error!\n");    
    }

    /*Если аргумент udp:
    1. Создаём сокет sock_dgram и заполняем структуру сервера
    2. Отправляем сообщение серверу и получаем ответ*/
    else if (strcmp(argv[1], "udp") == 0) {
        sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock_fd == -1)
            errExit("socket sock_dgram error!\n");

        memset(&servaddr, 0, sizeof(struct sockaddr_in));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr.s_addr);
        servaddr.sin_port = htons(UDP_PORT);

        if (sendto(sock_fd, message, 32, 0, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
            errExit("sendto error!\n");

        memset(message, 0, 32);
        if (recvfrom(sock_fd, message, 32, 0, NULL, NULL) == -1)
            errExit("recvfrom error!\n");

        printf("%s", message);

        if (close(sock_fd) == -1)
            errExit("close udp error!\n");
    } else {
        fprintf(stderr, "Usage:\n"
        "%s tcp - makes tcp client\n"
        "%s udp - makes udp client\n", argv[0], argv[0]);
        return -1;
    }

    return 0;
}