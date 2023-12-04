#include "../ip_udp_header.h"

void message_create(struct message *msg) {
                                                                /*Заполняем заголовок IP*/
  msg->ip.ip_ver_IHL = 0b01000101;                              /*В первые 4 бита записываем версию IP (версия 4)*/
                                                                /*В оставшиеся 4 записываем длину заголовка (20 байт)*/
  msg->ip.diffservice = 0;
  msg->ip.length = sizeof(struct message);                      /*Записываем длину всего пакета в сумме с данными*/
                                                                /*Также можно указать что угодно, потому что она заполнится автоматически*/
  msg->ip.identification = 0;                                   /*ID пакета оставляем 0 для автоматического заполнения*/
  msg->ip.flags_offset = 0b01000000;                            /*Ставим во 2ой бит 1, чтобы пакеты не фрагментировались*/
                                                                /*Остальные биты зануляем*/
  msg->ip.TTL = 0b01000000;                                     /*Time-to-Live ставим 64 (такое значение нашел в других пакетах в Wireshark)*/
  msg->ip.transport_proto = 0b00010001;                         /*Протокол транспортного уровня UDP (17)*/
  msg->ip.checksum = 0;                                         /*В чексумму ставим что угодно, она заполняется автоматически*/

  if (inet_pton(AF_INET, CLIENT_IP, &msg->ip.source_ip) == -1)  /*Переводим адреса IP источника и назначения из презентационного вида*/
    errExit("inet_pton source_ip error\n");                     /*в сетевой, также адрес источника можно указать 0 для автоматического*/
  if (inet_pton(AF_INET, SERV_IP, &msg->ip.dest_ip) == -1)      /*заполнения*/
    errExit("inet_pton dest_ip error\n");

                                                        /*Заполняем заголовок UDP*/
  msg->udp.source_port = htons(CLIENT_PORT_NUM);        /*Добвляем порт источника, который будем проверять далее*/
  msg->udp.destination_port = htons(SERV_PORT_NUM);     /*Порт назначения (сервера)*/
  msg->udp.length = htons(sizeof(struct udp_header));   /*Длина отправляемого пакета в сумме с заголовком*/
  msg->udp.checksum = 0;                                /*Чексумму оставляем нулевой*/
  strncpy(msg->udp.payload, "Hi!\0", strlen("Hi!\0"));  /*И заполняем payload*/
}