#include "../Posix_shmem.h"

int main() {
    int fd;
    char *buffer;
    sem_t *sem;

    fd = shm_open(SHMEM, O_CREAT | O_RDWR, 0666);
    if (fd == -1)
        errExit("shm_open error!\n");

    if (ftruncate(fd, 128) == -1)
        errExit("ftruncate error!\n");

    buffer = mmap(NULL, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buffer == NULL)
        errExit("mmap error!\n");

    sem = sem_open(SEM, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED)
        errExit("sem_open error!\n");

    if (sem_wait(sem) == -1)
        errExit("sem_wait error!\n");

    strncat(buffer, "Hello, i'm server!\n", 1 + strlen("Hello, i'm server!\n"));

    if (sem_wait(sem) == -1)
        errExit("sem_wait error!\n");

    printf("%s", buffer);

    if (munmap(buffer, 128) == -1)
        errExit("munmap error!\n");

    if (shm_unlink(SHMEM) == -1)
        errExit("shm_unlink error!\n");

    if (sem_close(sem) == -1)
        errExit("sem_close error!\n");

    if (sem_unlink(SEM) == -1)
        errExit("sem_unlink error!\n");

    return 0;
}