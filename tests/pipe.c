#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>




int main(int ac, char **av, char **env)
{
	int fd[2];

	/*
	 * fd[0] - read
	 * fd[1] - write
	 */

	char **ls_cmd = (char **)malloc(sizeof(char *)*3);
	ls_cmd[0] = strdup("/bin/ls");
	ls_cmd[1] = NULL;
	ls_cmd[2] = NULL;
	char **cat_cmd = (char **)malloc(sizeof(char *)*3);
	cat_cmd[0] = strdup("/bin/cat");
	cat_cmd[1] = strdup("-e");
	cat_cmd[2] = NULL;

	if (pipe(fd) == -1)
	{
		printf("error with opening the pipe!\n");
		return 1;
	}
	pid_t pid1 = fork();
	int status = 0;
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//child procces pid = 0
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		status = execve(ls_cmd[0], ls_cmd, NULL);
		exit(status);
	}
	waitpid(pid1, &status, 0);
//	printf("status = %d\n", status);
	if (WIFEXITED(status) != 0)
	{
		if (WEXITSTATUS(status) != 0)
		{
			printf("command not found!\n");
			exit(2);
		}
	}
	pid_t pid2 = fork();
	if (pid2 < 0)
		return 2;
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		status = execve(cat_cmd[0], cat_cmd, NULL);
		exit(status);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, &status, 0);
	printf("status = %d\n", status);
	if (WIFEXITED(status) != 0)
	{
		if (WEXITSTATUS(status) != 0)
		{
			printf("command not found!\n");
			exit(2);
		}
	}
	return 0;
}
