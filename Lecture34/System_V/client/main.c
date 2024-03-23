#include "../system_v_shmem.h"

int main() {
  key_t shmkey;
  key_t semkey;
  int shmid;
  int semid;
  char *buffer;
  struct sembuf lock[2] = {{0, 0, 0}, 
                           {0, 1, 0}};
  struct sembuf unlock = {0, -1, 0};
  shmkey = ftok(SHMEM_SEGMENT, PROJ_ID);
  if (shmkey == -1)
    errExit("ftok error\n");
  semkey = ftok(SEMAPHORE, PROJ_ID);
  if (semkey == -1)
    errExit("ftok sem error\n");
  shmid = shmget(shmkey, 128, 0);
  if (shmid == -1)
    errExit("shmget error\n");
  semid = semget(semkey, 1, IPC_CREAT | 0666);
  if (semid == -1)
    errExit("semget error\n");
  buffer = shmat(shmid, NULL, SHM_R);
  if (buffer == NULL)
    errExit("shmat shm_r error\n");
  printf("%s", buffer);
  if (shmdt(buffer) == -1)
    errExit("shmdt shm_r error\n");
  buffer = shmat(shmid, NULL, SHM_W);
  if (buffer == NULL)
    errExit("shmat shm_w error\n");
  strcpy(buffer, "Hi!\n");
  if (shmdt(buffer) == -1)
    errExit("shmdt shm_w error\n");
  semop(semid, lock, 2);
  return 0;
}