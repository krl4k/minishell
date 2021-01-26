/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:51:13 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 11:51:15 by fgrisell         ###   ########.fr       */
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
			status = execve(line,all->command_argv[0],env);
			exit(status);
		}
		else
		{
			wait(&status);
			printf("Выполнено успешно!\n");
		}
	}
}

int			execute(t_all *all, char **argv, char **env)
{
	if (all->flag & BIN_EXEC)
		bin_func(all, argv);
	else if (all->flag == PWD)



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