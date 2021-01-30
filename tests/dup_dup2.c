#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int ac, char **av, char **env)
{
//	int fd[2];
//	char c;
//	pipe(fd);
//
//	if (fork())
//	{ //родитель
//		close(fd[0]);
//		c = 0;
//		while (write(fd[1], &c, 1) > 0)
//		{
//			c++;
//		}
//	} else
//	{ //дочерний процесс
//		dup2(fd[0], 0); //подменили STDIN
//		close(fd[0]);
//		close(fd[1]);
//		execve("/bin/cat", NULL, env); //запустили новую программу для которой STDIN = pipe
//	}
//

	pid_t pid;
	int status = 0;
	int newfd;
//	char **argv = {strdup("-e", NULL};
	if ((pid = fork()) < 0)
		exit(0);
	if (pid == 0)
	{
		newfd = open("t.txt", O_WRONLY | O_CREAT, 0655);
		close(1);
		dup(newfd);
//		dup2(newfd, 1);
		close(newfd);
		write(1, "123\n", 4);
//		status = execve("cat", argv, env);
		exit(status);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
//			printf("status = %d\n", WEXITSTATUS(status));
			write(1, "ENDED!!!------\n", 15);
//		printf("ENDED!!!---------\n");
	}

//	int fd = open("t.txt", O_WRONLY, O_APPEND);
//	int fd_out = dup(fd);
//	dup2(fd, 1);
//	char *str = (char *)malloc(10);
//	scanf("%s", str);
//	printf("1\n");
//	dup2(fd_out, fd);
//	printf("2\n");
//	write(fd_out, "str", 3);
//	close(fd);

//
	return 0;
}