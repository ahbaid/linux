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

// {{{ int main(void)
// ----------------------------------------------------------------
int main(void) {

   // Get the process id (pid) and display it
   printf("\nPID[%d] parent(%d) waiting for signals, ready...\n",getpid(),getppid());

   if (signal(SIGINT, signal_handler) == SIG_ERR) {
      printf("\ncan't catch SIGINT\n");
   }

   // Infinite loop
   while(1) {
    sleep(1);
   }

   return 0;

}
// ----------------------------------------------------------------
// }}}
