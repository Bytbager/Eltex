#include "../server_type.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *client_thread_logic(void *temp) {
  int serverFD, servthreadFD;
  struct sockaddr_in servaddr, servthreadaddr;
  in_addr_t servip;
  char msgbuf[32];
  memset(msgbuf, 0, 32);
  int *number = (int *) temp;
  serverFD = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFD == -1)
    errExit("socket error\n");
  memset(&servaddr, 0, sizeof(struct sockaddr_in));
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, SERVER_IP, &servip);
  servaddr.sin_addr.s_addr = servip;
  servaddr.sin_port = htons(SERVER_PORT);
  if (connect(serverFD, (struct sockaddr *) &servaddr, sizeof(struct sockaddr_in)) == -1)
    errExit("connect error\n");
  if (recv(serverFD, &servthreadaddr, sizeof(struct sockaddr_in), 0) == -1)
    errExit("recv error\n");
  if (close(serverFD) == -1)
    errExit("close thread error\n");
  servthreadFD = socket(AF_INET, SOCK_STREAM, 0);
  if (servthreadFD == -1)
    errExit("servthread socket error\n");
  if (connect(servthreadFD, (struct sockaddr *) &servthreadaddr, sizeof(struct sockaddr_in)) == -1)
    errExit("connect servthread error\n");
  if (recv(servthreadFD, msgbuf, 32, 0) == -1)
    errExit("recv servthread error\n");
  printf("%d - %s", *number, msgbuf);
  if (close(servthreadFD) == -1)
    errExit("close servthread error\n");
  pthread_exit(NULL);
}