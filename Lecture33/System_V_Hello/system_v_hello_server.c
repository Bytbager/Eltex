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
    strcpy(sndmsg.text, "Hello!\n");
    struct message rcvmsg;
    queue_stoc_fd = open(QUEUE_PATHNAME_STOC, O_CREAT | 0666);  /*Сервер создает файл очереди для отправки клиенту*/
    if (queue_stoc_fd == -1)
        errExit("open error\n");
    queue_stoc_key = ftok(QUEUE_PATHNAME_STOC, PROJ_ID);        /*Получает уникальный ключ для создания очереди*/
    if (queue_stoc_key == -1)
        errExit("ftok error\n");
    msqid_stoc = msgget(queue_stoc_key, IPC_CREAT | 0666);      /*Создает очередь для отправки клиенту*/
    if (msqid_stoc == -1)
        errExit("msgget error\n");
    if (msgsnd(msqid_stoc, &sndmsg, sizeof(sndmsg.text), IPC_NOWAIT) == -1) /*Отправляет клиенту сообщение*/
        errExit("msgsnd error\n");
    queue_ctos_fd = open(QUEUE_PATHNAME_CTOS, O_CREAT | 0666);  /*Созает файл очереди для прослушивания клиента*/
    if (queue_ctos_fd == -1)
        errExit("open 2 error\n");
    queue_ctos_key = ftok(QUEUE_PATHNAME_CTOS, PROJ_ID);        /*Получает для нее уникальный ключ*/
    if (queue_ctos_key == -1)
        errExit("ftok 2 error\n");
    msqid_ctos = msgget(queue_ctos_key, IPC_CREAT | 0666);      /*Создает очередь для записи*/
    if (msqid_ctos == -1)
        errExit("msgget 2 error\n");
    recsz = msgrcv(msqid_ctos, &rcvmsg, 20, 1, MSG_NOERROR);    /*С ее помощью ожидает ответ от клиента*/
    if (recsz == -1)
        errExit("msgrcv error\n");
    printf("client: %s\n", rcvmsg.text);                        /*Когда получает ответ, выводит его на экран*/

    if (msgctl(msqid_stoc, IPC_RMID, NULL) == -1)               /*Удаляет первую очередь*/
        errExit("msgctl error\n");
    if (close(queue_stoc_fd) == -1)                             /*Закрывает дескриптор файла первой очереди*/
        errExit("close error\n");                               /*для последующего удаления*/
    if (unlink(QUEUE_PATHNAME_STOC) == -1)                      /*Удаляет файл*/
        errExit("unlink error\n");
    if (msgctl(msqid_ctos, IPC_RMID, NULL) == -1)               /*Проводит те же самые операции со второй очередью*/
        errExit("msgctl 2 error\n");
    if (close(queue_ctos_fd) == -1)
        errExit("close 2 error\n");
    if (unlink(QUEUE_PATHNAME_CTOS) == -1)
        errExit("unlink 2 error\n");
    return 0;
}