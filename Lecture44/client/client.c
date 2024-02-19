#include "../af_packet_sock_raw.h"

int main() {
  size_t bufsize = sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr) + 16;
  char *buffer = malloc(bufsize);
  if (buffer == NULL)
    errExit("malloc buffer error\n");
  memset(buffer, 0, bufsize);

  struct ether_header *ether = (struct ether_header *) buffer;
  struct iphdr *ip = (struct iphdr *) (buffer + sizeof(struct ether_header));
  struct udphdr *udp = (struct udphdr *) (buffer + sizeof(struct ether_header) + sizeof(struct iphdr));
  char *payload = buffer + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
  
  

  int server_fd;
  struct sockaddr_ll server;
  int flag = 1;
  char dest[32];
  memset(dest, 0 , 32);
  server_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); /*Создаем сокет типа SOCK_RAW, протокол UDP, семейства AF_INET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  
  memset(&server, 0, sizeof(struct sockaddr_ll));       /*Заполняем структуру сервера*/
  server.sll_family = AF_PACKET;
  server.sll_ifindex = if_nametoindex(VM_INDEX);
  server.sll_halen = 6;
  server.sll_addr[0] = 0x52;
  server.sll_addr[1] = 0x54;
  server.sll_addr[2] = 0x00;
  server.sll_addr[3] = 0x3e;
  server.sll_addr[4] = 0x23;
  server.sll_addr[5] = 0x63;

  message_create(&ether, &ip, &udp, &payload);                                 /*Заполняем сообщение серверу*/
  
  if (sendto(server_fd, buffer, bufsize, 0, (struct sockaddr *) &server, sizeof(struct sockaddr_ll)) == -1) /*Отправляем сообщение серверу*/
    errExit("send error\n");
  buffer += sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
  printf("Client: %s\n", buffer);
  buffer -= sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
  while (1) {
    if (recvfrom(server_fd, buffer, bufsize, 0, NULL, NULL) == -1) /*Получаем ответ от сервера, не сохраняем его эндпоинт, он нам не нужен*/
      errExit("recv error\n");
    inet_ntop(AF_INET, &ip->saddr, dest, 32);
    if (ether->ether_shost[0] == 0x52 && ether->ether_shost[5] == 0x63)
    printf("from - %x:%x:%x:%x:%x:%x, IP - %s\n", ether->ether_shost[0], ether->ether_shost[1], ether->ether_shost[2],
    ether->ether_shost[3], ether->ether_shost[4], ether->ether_shost[5], dest);
    /*Далее проверяем порт и адрес назначения, которые ранее мы указывали как порт и адрес источника в сообщении серверу*/
    if (ntohs(udp->dest) == CLIENT_PORT_NUM && strcmp(dest, CLIENT_IP) == 0) {   /*Если они совпал, выводим payload, и выходим из цикла*/
      printf("Server: %s\n", payload);
      break;
    }
  }
  free(buffer);
  if (close(server_fd) == -1)     /*Закрываем дескриптор сервера, завершаем программу*/
    errExit("close error\n");
  return 0;
}