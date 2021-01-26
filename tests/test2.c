#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
	printf("Будет выполнена программа %s...\n\n", argv[0]);
	printf("Выполняется %s", argv[0]);

	int i = 0;
	while (argv[++i])
		printf("argv[%d] = %s\n", i, argv[i]);

	return 0;
}
