#include "../client_sockraw.h"

int main() {
  int server_fd;
  struct sockaddr_in server;
  struct message sendbuffer, *recvbuffer;
  char *buffer = malloc(128);
  memset(buffer, 0, 128);
  socklen_t recvfr_len;
  server_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); /*Создаем сокет типа SOCK_RAW, протокол UDP, семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  memset(&server, 0, sizeof(struct sockaddr_in));       /*Заполняем структуру сервера*/
  server.sin_family = AF_INET;
  inet_pton(AF_INET, SERV_IP, &server.sin_addr.s_addr);
  server.sin_port = htons(SERV_PORT_NUM);

  memset(&sendbuffer, 0, sizeof(struct message));       /*Заполняем сообщение серверу*/
  sendbuffer.source_port = htons(CLIENT_PORT_NUM);      /*Добвляем порт источника, который будем проверять далее*/
  sendbuffer.destination_port = htons(SERV_PORT_NUM);   /*Порт назначения (сервера)*/
  sendbuffer.length = htons(sizeof(struct message));    /*Длина отправляемого пакета в сумме с заголовком*/
  sendbuffer.checksum = htons(0);                       /*Чексумму оставляем нулевой*/
  strncpy(sendbuffer.payload, "Hi!\0", strlen("Hi!\0"));/*И заполняем payload*/
  if (sendto(server_fd, &sendbuffer, sizeof(struct message), 0, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) /*Отправляем сообщение серверу*/
    errExit("send error\n");                            /*Отправляем сообщение серверу*/
  printf("Client: %s\n", sendbuffer.payload);
  while (1) {
    if (recvfrom(server_fd, buffer, 128, 0, NULL, NULL) == -1) /*Получаем ответ от сервера, не сохраняем его эндпоинт, он нам не нужен*/
      errExit("recv error\n");
                                                      /*В полученном сообщении пропускаем первые 20 байт, чтобы убрать IP заголовок*/
    recvbuffer = (struct message *) (buffer + 20);    /*Далее проверяем порт назначения, который ранее мы указывали как порт источника в сообщении серверу*/
    if (ntohs(recvbuffer->destination_port) == CLIENT_PORT_NUM) {   /*Если он совпал, выводим payload, и выходим из цикла*/
      printf("Server: %s\n", recvbuffer->payload);
      break;
    }
  }
  free(buffer);
  if (close(server_fd) == -1)     /*Закрываем дескриптор сервера, завершаем программу*/
    errExit("close error\n");
  return 0;
}