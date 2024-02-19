#ifndef __AF_PACKET_SOCK_RAW_H__
#define __AF_PACKET_SOCK_RAW_H__

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <malloc.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PC_INDEX "enp5s0"
#define VM_INDEX "virbrmgmt0"
#define PC_MAC "52:54:00:6b:47:fe"
#define VM_MAC "52:54:00:3e:23:63"
#define SERV_IP "192.168.33.2"
#define CLIENT_IP "192.168.33.1"
#define SERV_PORT_NUM 7777
#define CLIENT_PORT_NUM 7778

void errExit(char *errstr);
void message_create(struct ether_header **ether, struct iphdr **ip, struct udphdr **udp, char **payload);

#endif //__AF_PACKET_SOCK_RAW_H__