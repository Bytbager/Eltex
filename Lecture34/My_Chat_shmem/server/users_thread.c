#include "../my_chat_shmem.h"

void users_thread() {
    int key_shm, key_sem, fd_shm, fd_sem, shm_id, sem_id;
    struct user *user;
    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};

    /*Создаём участок разделяемой памяти*/

    fd_shm = open(SHMEM_USER, O_CREAT | O_RDWR, 0666);
    if (fd_shm == -1)
        errExit("open user error!\n");
    key_shm = ftok(SHMEM_USER, PROJ_ID);
    if (key_shm == -1)
        errExit("ftok users_thread error!\n");
    shm_id = shmget(key_shm, 20 * sizeof(struct user), IPC_CREAT | 0666);
    if (shm_id == -1)
        errExit("shmget users_thread error!\n");

    /*Создаём семафор*/

    fd_sem = open(SEMAPHORE_USERS, O_CREAT | O_RDWR, 0666);
    if (fd_sem == -1)
        errExit("open user error!\n");
    key_sem = ftok(SEMAPHORE_USERS, PROJ_ID);
    if (key_sem == -1)
        errExit("ftok users_thread error!\n");
    sem_id = semget(key_sem, 1, IPC_CREAT | 0666);
    if (sem_id == -1)
        errExit("semget users_thread error!\n");

    /*Подключаемся к памяти, чтобы занулить её*/

    user = shmat(shm_id, NULL, 0666);
    if (user == ((void *) -1))
        errExit("shmat users_thread error!\n");

    memset(user, 0, sizeof(struct user) * 20);
    
    while (1) {}
}