#include "../my_chat_shmem.h"

void message_thread() {
    int key_shm, key_sem, fd_shm, fd_sem, shm_id, sem_id;
    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};
    char *msg_buffer;

    /*Создаём участок разделяемой памяти*/

    fd_shm = open(SHMEM_MSG, O_CREAT | O_RDWR, 0666);
    if (fd_shm == -1)
        errExit("open message_thread error!\n");
    key_shm = ftok(SHMEM_MSG, PROJ_ID);
    if (key_shm == -1)
        errExit("ftok message_thread error!\n");
    shm_id = shmget(key_shm, 2048, IPC_CREAT | 0666);
    if (shm_id == -1)
        errExit("shmget message_thread error!\n");

    /*Создаём семафор*/

    fd_sem = open(SEMAPHORE_MSG, O_CREAT | O_RDWR, 0666);
    if (fd_sem == -1)
        errExit("open message_thread error!\n");
    key_sem = ftok(SEMAPHORE_MSG, PROJ_ID);
    if (key_sem == -1)
        errExit("ftok message_thread error!\n");
    sem_id = semget(key_sem, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
        errExit("semget message_thread error!\n");

    /*Подключаемся к памяти, чтобы занулить её*/

    msg_buffer = shmat(shm_id, NULL, 0666);
    if (msg_buffer == (void *) -1)
        errExit("shmat msg_buffer error!\n");

    memset(msg_buffer, 0, 2048);

    while (1) {}
}