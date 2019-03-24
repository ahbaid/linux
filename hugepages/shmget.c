#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>


/* 1M = 1048576 */
/* 2M = 2097152 */
/* 4M = 4194304 */
#define SHMSZ 4194304

int main() {

  printf("Huge Pages test with %d Byte Segment\n",SHMSZ);

  /*
  * key_t shmkey = 43805; ab1d
  * key_t shmkey = 3514;  dba
  * key_t shmkey = 5678;
  */
  key_t shmkey = 3514;


  /*
  * int shmflags = SHM_HUGETLB;
  * int shmflags = IPC_CREAT | 0666;
  * int shmflags = SHM_HUGETLB|IPC_CREAT|SHM_R|SHM_W;
  */
  int shmflags = SHM_HUGETLB|IPC_CREAT|SHM_R|SHM_W;


  /* Grab a shared memory segment */

  int shmid;

  if ((shmid = shmget(shmkey, SHMSZ, shmflags )) == -1) {
     perror("shmget");
  } else {
     printf("shmget returned %d\n",shmid);
  }


  /* Now attach to the segment */

  char *shmseg;

  if ((shmseg = shmat(shmid, NULL, 0)) == (char *) -1) {
     perror("shmat");
  } else {
     printf("%s\n","Attached");  
  }

  return 0;

}

