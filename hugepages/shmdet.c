// Author: Ahbaid Gaffoor
// Date:   23 April 2008
// File:   shmdet.c
// Use:    Test Shared Memory Detach

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>


/* 1M = 1048576 */
/* 2M = 2097152 */
/* 4M = 4194304 */
#define SHMSZ 4194304

int main() {

  printf("\nProcess Info: PID[%d] PPID[%d]\n",getpid(),getppid());
  printf("Huge Pages test with %d Byte Segment\n",SHMSZ);

  /*
  * key_t shmkey = 43805; ab1d
  * key_t shmkey = 3514;  dba
  * key_t shmkey = 5678;
  */
  key_t shmkey = 43805 ;

  /*
  * int shmflags = SHM_HUGETLB;
  * int shmflags = IPC_CREAT | 0666;
  * int shmflags = SHM_HUGETLB|IPC_CREAT|SHM_R|SHM_W;
  */
  int shmflags = SHM_HUGETLB|IPC_CREAT|SHM_R|SHM_W;

  /* Grab the shared memory segment, will allocate if it does not already exist with the given key */
  int shmid;
  if ((shmid = shmget(shmkey, SHMSZ, shmflags )) == -1) {
     perror("shmget");
  } else {
     printf("shmget returned %d\n",shmid);
  }

  /* Detach the segment */
  char *shmptr = shmat(shmid,NULL,0);
  if (shmdt(&shmptr) == -1) {
     perror("shmdt");
  } else {
     printf("%s\n","Detached....");  
  }

  return 0;

}

