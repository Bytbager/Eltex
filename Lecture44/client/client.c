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
  server_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); /*Создаем сокет типа SOCK_RAW, семейства AF_PACKET*/
  if (server_fd == -1)
    errExit("server_fd error\n");
  
  memset(&server, 0, sizeof(struct sockaddr_ll));       /*Заполняем структуру сервера*/
  server.sll_family = AF_PACKET;
  server.sll_protocol = htons(ETHERTYPE_IP);
  server.sll_ifindex = if_nametoindex(PC_INDEX);
  server.sll_halen = 6;
  server.sll_addr[0] = 0x52;
  server.sll_addr[1] = 0x54;
  server.sll_addr[2] = 0x00;
  server.sll_addr[3] = 0x83;
  server.sll_addr[4] = 0x2e;
  server.sll_addr[5] = 0x48;

  message_create(&ether, &ip, &udp, &payload);                                 /*Заполняем сообщение серверу*/
  
  if (sendto(server_fd, buffer, bufsize, 0, (struct sockaddr *) &server, sizeof(struct sockaddr_ll)) == -1) /*Отправляем сообщение серверу*/
    errExit("send error\n");
  buffer += sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
  printf("Client: %s\n", buffer);
  buffer -= sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct udphdr);
  
  uint32_t our_ip = 0;
  if (inet_pton(AF_INET, PC_IP, &our_ip) == -1)
    errExit("inet_pton our_ip error!\n");
  
  while (1) {
    memset(payload, 0, 16);
    if (recvfrom(server_fd, buffer, bufsize, 0, NULL, NULL) == -1) /*Получаем ответ от сервера, не сохраняем его эндпоинт, он нам не нужен*/
      errExit("recv error\n");

    unsigned short *pcheck = (short *)ip;         /*Вычисляем чексумму входящих пакетов и проверяем их целостность*/
    volatile unsigned int big_check = 0;
    unsigned short tmp = 0;

    for (int i = 0; i < 10; i++, pcheck++)
      big_check = big_check + *pcheck;

    tmp = big_check >> 16;
    *pcheck = (big_check & 0xFFFF) + tmp;
    
    if (*pcheck == MASK)
      printf("check good\n");
    else {
      printf("check bad\n");
      continue;
    }
    /*Далее проверяем порт и адрес назначения, которые ранее мы указывали как порт и адрес источника в сообщении серверу*/
    if (ntohs(udp->dest) == CLIENT_PORT_NUM && our_ip == ip->daddr) {   /*Если они совпал, выводим payload, и выходим из цикла*/
      printf("Server: %s\n", payload);
      break;
    }
  }
  free(buffer);
  if (close(server_fd) == -1)     /*Закрываем дескриптор сервера, завершаем программу*/
    errExit("close error\n");
  return 0;
}