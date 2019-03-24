# Handling Signals

## Linux Signals
~~~~
$ kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
~~~~

## Build signalhandler

### signalhandler.c
```C
// Author: Ahbaid Gaffoor
// Date:   Sunday 24th March 2019
// File:   signalhandler.c
// Use:    Test Signal handling

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

// {{{ signal_handler(int in_signal) -> void
// ----------------------------------------------------------------
void signal_handler(int in_signal) {
   if (in_signal == SIGINT) {
      printf("Received Signal[%d]....\n",SIGINT);
   }
}
// ----------------------------------------------------------------
// }}}

// {{{ void main()
// ----------------------------------------------------------------
void main() {

   // Get the process id (pid) and display it
   printf("\nPID[%d] parent(%d) waiting for signals, ready...\n",getpid(),getppid());

   if (signal(SIGINT, signal_handler) == SIG_ERR) {
      printf("\nCannot catch SIGINT\n");
   }

   // Infinite loop
   while(1) {
    sleep(1);
   }

}
// ----------------------------------------------------------------
// }}}
```

### Makefile
```
CC=gcc
signalhandler: signalhandler.c
        $(CC) -o signalhandler signalhandler.c
```

### make
~~~~
$ make
gcc -o signalhandler signalhandler.c
$ ls
makefile  signalhandler  signalhandler.c
~~~~

## Ctrl-C / SIGNIT - 2
~~~~
$ ./signalhandler

PID[8350] parent(29075) waiting for signals, ready...
^CReceived Signal[2]....
~~~~

## SIGINT - 2
### Session 1
~~~~
$ ps -ef|grep 8350
ahbaidg   8350 29075  0 14:39 pts/2    00:00:00 ./signalhandler
ahbaidg   8388  6260  0 14:41 pts/8    00:00:00 grep --color=auto 8350
$ sleep 3; kill -SIGINT 8350
~~~~
### Session 2
~~~~
Received Signal[2]....
Hangup
~~~~

## SIGKILL - 9
### Session 1
~~~~
$ ./signalhandler

PID[8493] parent(29075) waiting for signals, ready...
Killed
$ 
~~~~
### Session 2
~~~~
$ ps -ef|grep signalhandler | grep -v grep
ahbaidg   8493 29075  0 14:45 pts/2    00:00:00 ./signalhandler
$ kill -SIGKILL 8493
~~~~

## SIGHUP - 1
### Session 1
~~~~
$ ./signalhandler

PID[8729] parent(8710) waiting for signals, ready...
Hangup
$ 
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGHUP 8729
~~~~

## SIGINT - 2
### Session 1
~~~~
$ ./signalhandler

PID[8880] parent(8710) waiting for signals, ready...
Received Signal[2]....

~~~~
### Session 2
~~~~
$ ps -ef|grep signalhandler | grep -v grep
ahbaidg   8880  8710  0 15:01 pts/9    00:00:00 ./signalhandler
$ sleep 3; kill -SIGINT 8880
$ ps -ef|grep signalhandler | grep -v grep
ahbaidg   8880  8710  0 15:01 pts/9    00:00:00 ./signalhandler
~~~~

## SIGQUIT - 3
### Session 1
~~~~
$ ./signalhandler

PID[8880] parent(8710) waiting for signals, ready...
Received Signal[2]....
Quit (core dumped)
$ 
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGQUIT 8880
~~~~

## SIGKILL - 9
### Session 1
~~~~
$ ./signalhandler

PID[8941] parent(8710) waiting for signals, ready...
Killed
$ 
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGKILL 8941
~~~~

## SIGALRM - 14
### Session 1
~~~~
$ ./signalhandler

PID[8983] parent(8710) waiting for signals, ready...
Alarm clock
$ 
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGALRM 8983
~~~~

## SIGTERM - 15
### Session 1
~~~~
$ ./signalhandler

PID[9016] parent(8710) waiting for signals, ready...
Terminated
$ 
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGTERM 9016
~~~~

## SIGSYS - 31
### Session 1
~~~~
$ ./signalhandler

PID[9046] parent(8710) waiting for signals, ready...
Bad system call (core dumped)
$
~~~~
### Session 2
~~~~
$ sleep 3; kill -SIGSYS 9046
~~~~
