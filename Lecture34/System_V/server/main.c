#include "../system_v_shmem.h"

int main() {
  key_t shmkey;
  key_t semkey;
  int shm_fd;
  int sem_fd;
  int shmid;
  int semid;
  struct sembuf lock[2] = {{0, 0, 0}, 
                           {0, 1, 0}};
  struct sembuf unlock = {0, -1, 0};
  char *buffer;
  shm_fd = open(SHMEM_SEGMENT, O_CREAT | 0666);
  if (shm_fd == -1)
    errExit("open o_creat error\n");
  sem_fd = open(SEMAPHORE, O_CREAT | 0666);
  if (sem_fd == -1)
    errExit("open ocreat sem error\n");
  shmkey = ftok(SHMEM_SEGMENT, PROJ_ID);
  if (shmkey == -1)
    errExit("ftok error\n");
  semkey = ftok(SEMAPHORE, PROJ_ID);
  if (semkey == -1)
    errExit("ftok sem error\n");
  shmid = shmget(shmkey, 128, IPC_CREAT | 0666);
  if (shmid == -1)
    errExit("shmget error\n");
  semid = semget(semkey, 1, IPC_CREAT | 0666);
  if (semid == -1)
    errExit("semget error\n");
  buffer = shmat(shmid, NULL, SHM_W);
  if (buffer == NULL)
    errExit("shmat shm_w error\n");
  semop(semid, lock, 2);
  strcpy(buffer, "Hello!\n");
  if (shmdt(buffer) == -1)
    errExit("shmdt shm_w error\n");
  semop(semid, &unlock, 1);
  semop(semid, &unlock, 1);
  buffer = shmat(shmid, NULL, SHM_R);
  if (buffer == NULL)
    errExit("shmat shm_r error\n");
  printf("%s", buffer);
  if (shmdt(buffer) == -1)
    errExit("shmdt shm_r error\n");
  if (shmctl(shmid, IPC_RMID, NULL) == -1)
    errExit("shmctl error\n");
  if (semctl(semid, 1, IPC_RMID) == -1)
    errExit("semctl error\n");
  if (close(shm_fd) == -1)
    errExit("close error\n");
  if (unlink(SHMEM_SEGMENT) == -1)
    errExit("unlink error\n");
  if (close(sem_fd) == -1)
    errExit("close sem error\n");
  if (unlink(SEMAPHORE) == -1)
    errExit("unlink error\n");
  return 0;
}