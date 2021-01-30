
#include "minishell.h"

static int count_cmd_after_pipe(t_all *all, int pos)
{
	int i;

	i = 0;
	while (all->command_argv[pos])
	{
		i++;
	}
	return (i);
}

int pipes(t_all *all, int pos_pipe)
{
	printf("pipes start\n");
	char **command1;
	char **command2;
	int fd[2];

	/*
	* fd[0] - read
	* fd[1] - write
	*/

	printf("all-> pipe = %s\n", all->command_argv[pos_pipe]);
	int count_after_pipe = count_cmd_after_pipe(all, pos_pipe);
	if (!(command1 = (char **)malloc(sizeof(char *) * (pos_pipe + 1))))
		return(0);
	if (!(command2 = (char **)malloc(sizeof(char *) * (pos_pipe + 1))))
		return(0);

	int i = 0;

	while (i < count_after_pipe)
	{
		printf("str[%d] = %s", i , all->command_argv[i]);
		command1[i] = ft_strdup(all->command_argv[i]);
		i++;
	}
	i++;
	while (all->command_argv[i])
	{
		command2[i] = ft_strdup(all->command_argv[i]);
		i++;
	}
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
		status = execve(command1[0], command1, NULL);
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
		status = execve(command2[0], command2, NULL);
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