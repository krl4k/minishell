#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
   int rv;

   rv = 1;
   switch(rv) {
  case 1:
			printf("tut2\n");
  case 0:
 			printf("Ya tut\n");
  default:
			printf("Введите цифру:");
			scanf("%d", &rv);
   }
}
