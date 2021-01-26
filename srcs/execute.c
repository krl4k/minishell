/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:51:13 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 13:41:21 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		my_builtin(char *command)
{

}

void bin_func(t_all  *all, char **env)
{
	int status;
	char *line;

	while (1)
	{
		pid_t pid = fork();
		if (pid < 0)
			perror("fork()\n");
		if (pid == 0)
		{
			printf("bin func: CHILD:\n");
			status = execve(line,all->command_argv,env);
			exit(status);
		}
		else
		{
			wait(&status);
			printf("Выполнено успешно!\n");
		}
	}
}

int			execute(t_all *all, char *line, char **argv, char **env)
{
	printf("execute---------------------\n");
	if (all->bin_command)
	{
		printf("BIN_EXEC\n");
		bin_func(all, argv);
	}
	return 0;
	/*pid_t pid = fork();
	if (pid < 0)
		perror("fork()\n");
	if (pid == 0)
	{
//		printf("CHILD:\n");
		status = execve(,argv,env);
		exit(status);
	}
	else
	{
		wait(&status);
		printf("Выполнено успешно!\n");
	}*/

	return (EXIT_SUCCESS);
}