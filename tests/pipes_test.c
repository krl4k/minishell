
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int pipes_func(int value, int pipes)
{
	int fd[2];
	if (pipe(fd) < 0)
		perror("pipe error");

	pid_t pid;

	if (pipes == 0)
		return value;
	if (pipe(fd) < 0)
		return 1;
	if ((pid = fork()) < 0)
		return 1;
	if (pid == 0)
	{
		int x;
		read(fd[0], &x, sizeof(int));
		x *= 2;
		close(fd[0]);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
		pipes_func(x, pipes - 1);
	}
	else
	{
		int x = value;
//		printf("enter a number: ");
//		scanf("%d", &x);

		write(fd[1], &x, sizeof(int));
		close(fd[1]);
		wait(&pid);
		read(fd[0], &x, sizeof(int));
		printf("x = %d\n", x);
		close(fd[0]);
	}
	write(1, &value, sizeof(int));
	return value;
}


int main(int ac, char **av, char **env)
{
	int value = 5;
	pipes_func(value, 3);

	printf("value = %d\n", value);
}
