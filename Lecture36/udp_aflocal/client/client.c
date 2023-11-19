#include "../aflocal_sockdgram.h"

int main() {
  int server_fd;
  struct sockaddr_un server, client;
  char *recvbuffer, *sendbuffer;
  sendbuffer = malloc(16);
  strncpy(sendbuffer, "Hi!\0", strlen("Hi!\0"));
  server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);  /*Создаем датаграмный сокет семейства AF_LOCAL*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&client, 0, sizeof(struct sockaddr_un)); /*Заполняем структуру клиента*/
  client.sun_family = AF_LOCAL;
  strncpy(client.sun_path, CLIENT_SUN_PATH, strlen(CLIENT_SUN_PATH));
  if (bind(server_fd, (struct sockaddr *) &client, sizeof(struct sockaddr_un)) == -1) /*Выполняем привязку структуры клиента к сокету сервера*/
    errExit("bind error\n");
  memset(&server, '\0', sizeof(struct sockaddr_un));  /*Заполняем структуру сервера*/
  server.sun_family = AF_LOCAL;
  strncpy(server.sun_path, SERVER_SUN_PATH, strlen(SERVER_SUN_PATH));
  if (connect(server_fd, (struct sockaddr *) &server, sizeof(struct sockaddr_un)) == -1)  /*Подключаемся к серверу*/
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
  if (close(server_fd) == -1) /*Закрываем сокет сервера*/
    errExit("close error\n");
  free(recvbuffer);           /*Очищаем буфферы, завершаем программу*/
  free(sendbuffer);
  return 0;
}