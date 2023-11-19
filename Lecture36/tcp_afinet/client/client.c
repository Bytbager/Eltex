#include "../afinet_sockstream.h"

int main() {
  int server_fd;
  struct sockaddr_in server;
  char *recvbuffer, *sendbuffer;
  sendbuffer = malloc(16);
  strncpy(sendbuffer, "Hi!\0", strlen("Hi!\0"));
  server_fd = socket(AF_INET, SOCK_STREAM, 0);    /*Создаем потоковый сокет семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&server, 0, sizeof(struct sockaddr_in)); /*Заполняем структуру сервера sockaddr_in*/
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = SERVER_PORT;
  if (connect(server_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1)  /*Подключаемся к серверу*/
    errExit("connect error\n");
  if (send(server_fd, sendbuffer, strlen(sendbuffer), 0) == -1) /*Отправляем сообщение серверу*/
    errExit("send error\n");
  printf("Client: %s\n", sendbuffer);
  recvbuffer = malloc(16);
  if (recvbuffer == NULL)
    errExit("malloc error\n");
  if (recv(server_fd, recvbuffer, 16, 0) == -1) /*Получаем ответ от сервера*/
    errExit("recv error\n");
  printf("Server: %s\n", recvbuffer);
  if (close(server_fd) == -1) /*Закрываем дескриптор, очищаем буфферы, завершаем программу*/
    errExit("close error\n");
  free(recvbuffer);
  free(sendbuffer);
  return 0;
}