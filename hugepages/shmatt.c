// Author: Ahbaid Gaffoor
// Date:   23 April 2008
// File:   shmatt.c
// Use:    Test Shared Memory Allocation

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

  /* Grab a shared memory segment, will allocate if it does not already exist with the given key */
  int shmid;
  if ((shmid = shmget(shmkey, SHMSZ, shmflags )) == -1) {
     perror("shmget");
  } else {
     printf("shmget returned %d\n",shmid);
  }

  /* Attach to the segment & loop if found */
  char *shmseg;
  if ((shmseg = shmat(shmid, NULL, 0)) == (char *) -1) {
     perror("shmat");
  } else {
     printf("%s\n","Attached.... looping to hold attachment");  
     while (1) {
        sleep(1);
     }
  }

  return 0;

}

