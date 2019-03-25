# HugePages

## Code
### shmget.c
```C
// Author: Ahbaid Gaffoor
// Date:   23 April 2008
// File:   shmget.c
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

  /* Allocate a shared memory segment */
  int shmid;
  if ((shmid = shmget(shmkey, SHMSZ, shmflags )) == -1) {
     perror("shmget");
  } else {
     printf("shmget returned %d\n",shmid);
  }

  return 0;

}
```

### shmatt.c
```C
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
```

### Makefile
```
CC=gcc
shmatt: shmatt.c
	$(CC) -o shmatt shmatt.c

shmget: shmget.c
	$(CC) -o shmget shmget.c

shmdet: shmdet.c
	$(CC) -o shmdet shmdet.c
```

## Allocation Attempt

### Try to allocate a huge page - FAILS
~~~~
$ ./shmget 

Process Info: PID[10290] PPID[9862]
Huge Pages test with 4194304 Byte Segment
shmget: Cannot allocate memory
shmat: Invalid argument
~~~~

### Check HugePage alloaction - NONE, note pages are at 2M each
~~~~
$ grep -i Huge /proc/meminfo 
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
~~~~

### Check kernel configuration - None allocated
~~~~
$ sudo sysctl -a | grep ^vm.nr_huge
vm.nr_hugepages = 0
vm.nr_hugepages_mempolicy = 0
vm.nr_hugepages = 0
vm.nr_hugepages_mempolicy = 0
vm.nr_overcommit_hugepages = 0
~~~~

## Allocate Huge Pages
### Allocate 10 pages at 2M each = 20M
~~~~
$ sudo sysctl vm.nr_hugepages = 10
$ sudo sysctl -a | grep vm.nr
vm.nr_hugepages = 10
vm.nr_hugepages_mempolicy = 10
vm.nr_overcommit_hugepages = 0
~~~~


## Allocate Huge Page Memory Segment
### Allocate 
~~~~
$ ./shmget 

Process Info: PID[10354] PPID[9862]
Huge Pages test with 4194304 Byte Segment
shmget returned 131072
Attached
~~~~

### Attach to segment
~~~~
$ ./shmatt &
[1] 13252
$ 
Process Info: PID[13252] PPID[9862]
Huge Pages test with 4194304 Byte Segment
shmget returned 131072
Attached.... looping to hold attachment

$ ./shmatt &
[2] 13253
$ 
Process Info: PID[13253] PPID[9862]
Huge Pages test with 4194304 Byte Segment
shmget returned 131072
Attached.... looping to hold attachment

~~~~


### Validate - Note forced use of key "ab1d" :)
~~~~
$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
0x0000ab1d 131072     ahbaidg    600        4194304    2                     
~~~~~

## Destroy segment
~~~~
$ ipcrm -m 131072
$ ipcs -m

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
~~~~

