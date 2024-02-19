#include "../af_packet_sock_raw.h"

void message_create(struct ether_header **ether, struct iphdr **ip, struct udphdr **udp, char **payload) {

  (*ether)->ether_dhost[0] = 0x52;
  (*ether)->ether_dhost[1] = 0x54;
  (*ether)->ether_dhost[2] = 0x00;
  (*ether)->ether_dhost[3] = 0x3e;
  (*ether)->ether_dhost[4] = 0x23;
  (*ether)->ether_dhost[5] = 0x63;

  (*ether)->ether_shost[0] = 0x52;
  (*ether)->ether_shost[1] = 0x54;
  (*ether)->ether_shost[2] = 0x00;
  (*ether)->ether_shost[3] = 0x6b;
  (*ether)->ether_shost[4] = 0x47;
  (*ether)->ether_shost[5] = 0xfe;

  (*ether)->ether_type = ETH_P_IP;
                                                                /*Заполняем заголовок IP*/
  (*ip)->version = 4;                                          /*В первые 4 бита записываем версию IP (версия 4)*/
  (*ip)->ihl = 5;                                              /*В оставшиеся 4 записываем длину заголовка (20 байт)*/
  (*ip)->tos = 0;
  (*ip)->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 16;                      /*Записываем длину всего пакета в сумме с данными*/
                                                                 /*Также можно указать что угодно, потому что она заполнится автоматически*/
  (*ip)->id = 0;                                                /*ID пакета оставляем 0 для автоматического заполнения*/
  (*ip)->frag_off = 0b01000000;                                 /*Ставим во 2ой бит 1, чтобы пакеты не фрагментировались*/
                                                                 /*Остальные биты зануляем*/
  (*ip)->ttl = 0b01000000;                                      /*Time-to-Live ставим 64 (такое значение нашел в других пакетах в Wireshark)*/
  (*ip)->protocol = 0b00010001;                                 /*Протокол транспортного уровня UDP (17)*/
  (*ip)->check = 0;                                             /*В чексумму ставим что угодно, она заполняется автоматически*/

  if (inet_pton(AF_INET, CLIENT_IP, &(*ip)->saddr) == -1)       /*Переводим адреса IP источника и назначения из презентационного вида*/
    errExit("inet_pton source_ip error\n");                      /*в сетевой, также адрес источника можно указать 0 для автоматического*/
  if (inet_pton(AF_INET, SERV_IP, &(*ip)->daddr) == -1)         /*заполнения*/
    errExit("inet_pton dest_ip error\n");

                                                        /*Заполняем заголовок UDP*/
  (*udp)->source = htons(CLIENT_PORT_NUM);             /*Добвляем порт источника, который будем проверять далее*/
  (*udp)->dest = htons(SERV_PORT_NUM);                 /*Порт назначения (сервера)*/
  (*udp)->len = htons(sizeof(struct udphdr) + 16);          /*Длина отправляемого пакета в сумме с заголовком*/
  (*udp)->check = 0;                                   /*Чексумму оставляем нулевой*/
  strncpy(*payload, "Hi!\0", strlen("Hi!\0"));      /*И заполняем payload*/

}