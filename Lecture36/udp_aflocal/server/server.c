#include "../aflocal_sockdgram.h"

int main() {
  int server_fd;
  char *recvbuffer, *sendbuffer;
  struct sockaddr_un server, client;
  socklen_t client_len;
  sendbuffer = malloc(16);
  strncpy(sendbuffer, "Hello!\0", strlen("Hello!\0"));
  server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);  /*Создаем датаграмный сокет семейства AF_LOCAL*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&server, '\0', sizeof(struct sockaddr_un));  /*Заполняем структуру сервера*/
  server.sun_family = AF_LOCAL;
  strncpy(server.sun_path, SERVER_SUN_PATH, strlen(SERVER_SUN_PATH));
  if (bind(server_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) == -1) /*Выполняем привязку структуры сервера к сокету*/
    errExit("bind error\n");
  recvbuffer = malloc(16);
  if (recvbuffer == NULL)
    errExit("malloc error\n");
  client_len = sizeof(struct sockaddr_un);      /*Инициализируем переменную размера структуры клиента для получения его эндпоинта*/
  if (recvfrom(server_fd, recvbuffer, 16, 0, (struct sockaddr *) &client, &client_len) == -1) /*Получаем сообщение клиента и его эндпоинт*/
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