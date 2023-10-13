#include "mkfifo.h"

/*
Функция создает очередь SERVER_FIFO и открывает ее для записи,
после этого отправляет в нее сообщение для клиента, после
этого открывает очередь CLIENT_FIFO для чтения и ожидает сообщение клиента,
чтобы вывести его на экран.
*/
int main() {
    int serverFd;
    int clientFd;
    char message[32];
    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR) == -1 && errno != EEXIST) {
        perror("mkfifo server\n");
        _exit(-1);
    }
    serverFd = open(SERVER_FIFO, O_WRONLY);
    if (serverFd == -1) {
        perror("open serverFd\n");
        _exit(-1);
    }
    write(serverFd, "Hello!\n", strlen("Hello!\n"));
    clientFd = open(CLIENT_FIFO, O_RDONLY);
    if (clientFd == -1) {
        perror("open clientFd\n");
        _exit(-1);
    }
    read(clientFd, message, 32);
    write(1, message, strlen(message));
    close(serverFd);
    close(clientFd);
    return 0;
}