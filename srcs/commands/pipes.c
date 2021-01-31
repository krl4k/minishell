
#include "minishell.h"

static int count_cmd_after_pipe(t_all *all, int pos)
{
	int i;

	i = 0;
	while (all->command_argv[pos])
	{
		i++;
		pos++;
	}
	return (i);
}


char **commands(t_all *all, int start, int end)
{
	char	**commands;
	int		i;

	i = 0;
	if (!(commands = (char **) ft_calloc(start - end + 1, sizeof(char *))))
		return NULL;
	while (start < end)
	{
//		printf("command%d = %s\n", i, all->command_argv[start]);
		commands[i] = ft_strdup(all->command_argv[start]);
		start++;
		i++;
	}
	commands[i] = NULL;
	return (commands);
}


int pipes(t_all *all, int pos_pipe)
{
//	printf("pipes start\n");
	char **command1;
	char **command2;
	int fd[2];
	/*
	* fd[0] - read
	* fd[1] - write
	*/
	printf("all-> pipe = %s\n", all->command_argv[pos_pipe]);
	int count_after_pipe = count_cmd_after_pipe(all, pos_pipe);
//	if (!(command1 = (char **)ft_calloc((pos_pipe + 1), sizeof(char *))))
//		return(0);
//	if (!(command2 = (char **)ft_calloc((pos_pipe + 1), sizeof(char *))))
//		return(0);

	int i = 0;

	command1 = commands(all, 0, pos_pipe);
	printf("count after pipe = %d\n", count_after_pipe);
	command2 = commands(all, pos_pipe + 1, pos_pipe + count_after_pipe);

	while (command1[i])
	{
		printf("commands1[%d] = %s\n", i, command1[i]);
		i++;
	}
	i = 0;
	while (command2[i])
	{
		printf("commands2[%d] = %s\n",i, command2[i]);
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
			printf("1 command not found!\n");
//			exit(2);
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
			printf("2 command not found!\n");
//			exit(2);
		}
	}
	return 0;

}