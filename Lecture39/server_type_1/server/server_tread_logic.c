#include "../server_type.h"

extern pthread_mutex_t m1;

void *server_thread_logic(void *temp) {
  time_t result;
  int serverFD, clientFD;
  struct sockaddr_in cliaddr;
  socklen_t client_len;
  struct sockaddr_in *servaddr = (struct sockaddr_in *) temp;
  char msgbuf[32];
  memset(msgbuf, 0, 32);
  serverFD = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFD == -1)
    errExit("socket thread error\n");
  if (bind(serverFD, (struct sockaddr *) servaddr, sizeof(struct sockaddr_in)) == -1)
    errExit("bind thread error\n");
  if (listen(serverFD, 1) == -1)
    errExit("listen thread error\n");
  client_len = sizeof(struct sockaddr_in);
  clientFD = accept(serverFD, (struct sockaddr *) &cliaddr, &client_len);
  if (clientFD == -1)
    errExit("accept thread error\n");
  result = time(NULL);
  strcat(msgbuf, asctime(localtime(&result)));
  if (send(clientFD, msgbuf, strlen(msgbuf), 0) == -1)
      errExit("send error\n");
  if (close(clientFD) == -1)
      errExit("close cli error\n");
  if (close(serverFD) == -1)
    errExit("close serverFD thread error\n");
  pthread_exit(NULL);
}