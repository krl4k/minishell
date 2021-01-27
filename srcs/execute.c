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
/*!
** checks the /bin/ prefix
** \author fgrisell
*/
static int is_prefix_bin(char *line)
{
	if (ft_strncmp("/bin/", line, 5) == 1)
		return (1);
	return (0);
}

char *check_bin_func(t_all *all)
{
	char *line;

	if (is_prefix_bin(all->command_argv[0]))
		return all->command_argv[0];
	else
	{
		line = ft_strjoin("/bin/", all->command_argv[0]);
	}
	printf("command = %s\n", line);
	return (line);
}

/*!
** \author fgrisell
**
*/
void bin_func(t_all *all, char **env)
{
	int status;
	char *command;

	pid_t pid = fork();
	if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	if (pid == 0)
	{
//		printf("bin func: CHILD:\n");
		status = execve(all->command_argv[0], all->command_argv, env);
		exit(status);
	} else
	{
		wait(&status);
		printf("Выполнено успешно!\n");
	}
}

int execute(t_all *all, char *line, char **argv, char **env)
{
//	printf("execute---------------------\n");
	if (all->c_bin_command)
	{
//		printf("BIN_EXEC\n");
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