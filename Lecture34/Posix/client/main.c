#include "../Posix_shmem.h"

int main() {
    int fd;
    sem_t *sem;
    char *buffer;

    fd = shm_open(SHMEM, O_RDWR, 0666);
    if (fd == -1)
        errExit("shm_open error!\n");

    buffer = mmap(NULL, 128, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buffer == NULL)
        errExit("mmap error!\n");

    printf("%s", buffer);

    memset(buffer, 0, 128);

    strncat(buffer, "Hello, i'm client!\n", strlen("Hello, i'm client!\n") + 1);

    if (munmap(buffer, 128) == -1)
        errExit("munmap error!\n");

    sem = sem_open(SEM, O_RDWR);
    if (sem == SEM_FAILED)
        errExit("sem_open error!\n");
    
    if (sem_post(sem) == -1)
        errExit("sem_post error!\n");

    if (sem_close(sem) == -1)
        errExit("sem_close error!\n");

    return 0;
}