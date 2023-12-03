#include "../client_sockraw.h"

int main() {
  int server_fd;
  char *recvbuffer, *sendbuffer;
  struct sockaddr_in server, client;
  socklen_t client_len;
  sendbuffer = malloc(16);
  strncpy(sendbuffer, "Hello!\0", strlen("Hello!\0"));
  server_fd = socket(AF_INET, SOCK_DGRAM, 0); /*Создаем датаграммный сокет семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&server, '\0', sizeof(struct sockaddr_in));  /*Заполняем структуру сервера*/
  server.sin_family = AF_INET;
  inet_pton(AF_INET, SERV_IP, &server.sin_addr.s_addr);
  server.sin_port = htons(7777);
  if (bind(server_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) /*Выполняем привязку структуры сервера к сокету*/
    errExit("bind error\n");
  recvbuffer = malloc(16);
  if (recvbuffer == NULL)
    errExit("malloc error\n");
  client_len = sizeof(struct sockaddr_in);    /*Инициализируем переменную размера структуры клиента для получения эндпоинта*/
  if (recvfrom(server_fd, recvbuffer, 16, 0, (struct sockaddr *) &client, &client_len) == -1) /*Получаем сообщение от клиента и заполняем его эндпоинт*/
    errExit("recvfrom error\n");
  printf("Client: %s\n", recvbuffer);
  if (sendto(server_fd, sendbuffer, strlen(sendbuffer), 0, (struct sockaddr *) &client, client_len) == -1)  /*Отправляем ответ клиенту*/
    errExit("send error\n");
  printf("Server: %s\n", sendbuffer);
  if (close(server_fd) == -1)         /*Закрываем дескриптор сервера*/
    errExit("close server_fd error\n");
  free(recvbuffer);                   /*Очищаем буфферы, завершаем программу*/
  free(sendbuffer);
  return 0;
}