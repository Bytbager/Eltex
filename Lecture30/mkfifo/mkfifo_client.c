#include "mkfifo.h"

/*
Функция открывает очередь SERVER_FIFO для получения из нее
сообщения от сервера и вывода его на экран, после этого она
создает очередь для записи CLIENT_FIFO и отправляет ответ серверу.
*/
int main() {
    int serverFd;
    int clientFd;
    char message[32];
    serverFd = open(SERVER_FIFO, O_RDONLY);
    if (serverFd == -1) {
        perror("open serverFd\n");
        _exit(-1);
    }
    read(serverFd, message, 32);
    write(1, message, strlen(message));
    if (mkfifo(CLIENT_FIFO, S_IRUSR | S_IWUSR) == -1 && errno != EEXIST) {
        perror("mkfifo client\n");
        _exit(-1);
    }
    clientFd = open(CLIENT_FIFO, O_WRONLY);
    if (clientFd == -1) {
        perror("open clientFd\n");
        _exit(-1);
    }
    write(clientFd, "Hi!\n", strlen("Hi!\n"));
    close(serverFd);
    close(clientFd);
    return 0;
}