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

#define MASK 0b1111111111111111
#define PC_INDEX "br-enp2s0"
#define PC_MAC "6e:ef:a1:c2:4f:95"
#define VM_MAC "52:54:00:83:2e:48"
#define PC_IP "192.168.1.207"
#define VM_IP "192.168.1.142"
#define SERV_PORT_NUM 7777
#define CLIENT_PORT_NUM 7778

void errExit(char *errstr);
void message_create(struct ether_header **ether, struct iphdr **ip, struct udphdr **udp, char **payload);

#endif //__AF_PACKET_SOCK_RAW_H__