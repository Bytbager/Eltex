#include "../ip_udp_header.h"

int main() {
  int server_fd;
  struct sockaddr_in server;
  struct udp_header *udp_recvbuffer;
  struct ip_header *ip_recvbuffer;
  struct message msg;
  size_t bufsize = sizeof(struct ip_header) + sizeof(struct udp_header);
  int flag = 1;
  char *buffer = malloc(sizeof(struct message));
  if (buffer == NULL)
    errExit("malloc buffer error\n");
  char dest[32];
  memset(dest, 0 , 32);
  server_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); /*Создаем сокет типа SOCK_RAW, протокол UDP, семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  if (setsockopt(server_fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) == -1) /*Ставим опцию для сокета, позволяющую вручную заполнить заголовок IP*/
    errExit("setsockopt error\n");
  memset(&server, 0, sizeof(struct sockaddr_in));       /*Заполняем структуру сервера*/
  server.sin_family = AF_INET;
  inet_pton(AF_INET, SERV_IP, &server.sin_addr.s_addr);
  server.sin_port = htons(SERV_PORT_NUM);
  struct ip_header *temp;
  
  memset(&msg, 0, sizeof(struct message));
  message_create(&msg);                                 /*Заполняем сообщение серверу*/
  
  if (sendto(server_fd, &msg, sizeof(struct message), 0, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) /*Отправляем сообщение серверу*/
    errExit("send error\n");
  printf("Client: %s\n", msg.udp.payload);
  while (1) {
    if (recvfrom(server_fd, buffer, bufsize, 0, NULL, NULL) == -1) /*Получаем ответ от сервера, не сохраняем его эндпоинт, он нам не нужен*/
      errExit("recv error\n");
    ip_recvbuffer = (struct ip_header *) buffer;
    inet_ntop(AF_INET, &ip_recvbuffer->dest_ip, dest, 32);
    udp_recvbuffer = (struct udp_header *) (buffer + 20);
    
    /*Далее проверяем порт и адрес назначения, которые ранее мы указывали как порт и адрес источника в сообщении серверу*/
    if (ntohs(udp_recvbuffer->destination_port) == CLIENT_PORT_NUM && strcmp(dest, CLIENT_IP) == 0) {   /*Если они совпал, выводим payload, и выходим из цикла*/
      printf("Server: %s\n", udp_recvbuffer->payload);
      break;
    }
  }
  free(buffer);
  if (close(server_fd) == -1)     /*Закрываем дескриптор сервера, завершаем программу*/
    errExit("close error\n");
  return 0;
}