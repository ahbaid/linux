#include <stdio.h>

int main(argc, argv) int argc; char *argv[]; {
   printf("Args test\n");
   printf("arg[0] is: %s\n",argv[0]);
   printf("Args are: %d\n",argc);
   return 0;
}

