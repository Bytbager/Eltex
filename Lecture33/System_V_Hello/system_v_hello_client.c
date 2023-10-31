#include "system_v_hello.h"

struct message {
    long prio;
    char text[20];
};

int main() {
    key_t queue_stoc_key;
    key_t queue_ctos_key;
    int queue_stoc_fd;
    int queue_ctos_fd;
    int msqid_stoc;
    int msqid_ctos;
    int recsz;
    struct message sndmsg;
    sndmsg.prio = 1;
    strcpy(sndmsg.text, "Hi!\n");
    struct message rcvmsg;
    queue_stoc_key = ftok(QUEUE_PATHNAME_STOC, PROJ_ID);    /*Клиент получает уникальный ключ для прослушивания сервера*/
    if (queue_stoc_key == -1)
        errExit("ftok error\n");
    msqid_stoc = msgget(queue_stoc_key, 0);                 /*С его помощью открывает очередь*/
    if (msqid_stoc == -1)
        errExit("msgget error\n");
    queue_ctos_key = ftok(QUEUE_PATHNAME_CTOS, PROJ_ID);    /*За этим получает ключ для отправки сообщений серверу*/
    if (queue_ctos_key == -1)
        errExit("ftok 2 error\n");
    msqid_ctos = msgget(queue_ctos_key, 0);                 /*И также открывает вторую очередь*/
    if (msqid_ctos == -1)
        errExit("msgget 2 error\n");
    recsz = msgrcv(msqid_stoc, &rcvmsg, 20, 1, MSG_NOERROR);/*Считывает сообщение от сервера*/
    if (recsz == -1)
        errExit("msgrcv error\n");
    printf("server: %s\n", rcvmsg.text);                    /*Выводит его на экран*/
    if (msgsnd(msqid_ctos, &sndmsg, sizeof(sndmsg.text), IPC_NOWAIT) == -1) /*Отправляет серверу ответ*/
        errExit("msgsnd error\n");
    return 0;
}