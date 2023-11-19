#include "../afinet_sockstream.h"

int main() {
  int server_fd, new_fd;
  char *recvbuffer, *sendbuffer;
  sendbuffer = malloc(16);
  strncpy(sendbuffer, "Hello!\0", strlen("Hello!\0"));
  socklen_t client_addr_len;
  struct sockaddr_in server, client;
  server_fd = socket(AF_INET, SOCK_STREAM, 0);  /*Создаем потоковый сокет семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&server, '\0', sizeof(struct sockaddr_in));  /*Заполняем структуру сервера sockaddr_in*/
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = SERVER_PORT;
  if (bind(server_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) /*Выполняем привязку структуры сервера к сокету*/
    errExit("bind error\n");
  if (listen(server_fd, 5)  == -1)  /*Переводим сокет в пассивыный режим прослушивания*/
    errExit("listen error\n");
  new_fd = accept(server_fd, (struct sockaddr *) &client, &client_addr_len);  /*Ожидаем подключения клиентов и получаем их дескрипторы*/
  if (new_fd == -1)
    errExit("new_fd error\n");
  recvbuffer = malloc(16);
  if (recvbuffer == NULL)
    errExit("malloc error\n");
  if (recv(new_fd, recvbuffer, 16, 0) == -1)  /*Получаем сообщение от клиента*/
    errExit("recv error\n");
  printf("Client: %s\n", recvbuffer);
  if (send(new_fd, sendbuffer, strlen(sendbuffer), 0) == -1)  /*Отправляем ответ клиенту*/
    errExit("send error\n");
  printf("Server: %s\n", sendbuffer);
  if (close(new_fd) == -1)            /*Закрываем дескриптор клиента*/
    errExit("close new_fd error\n");
  if (close(server_fd) == -1)         /*Закрываем свой дескриптор*/
    errExit("close server_fd error\n");
  free(recvbuffer);                   /*Очищаем буфферы, завершаем программу*/
  free(sendbuffer);
  return 0;
}