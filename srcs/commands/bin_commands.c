/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:54:52 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 10:54:53 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
** checks the /bin/ prefix
** \author fgrisell
*/
static int is_prefix_bin(char *line)
{
	if (ft_strncmp("/bin/", line, 5) == 0)
		return (1);
	return (0);
}

char *check_bin_func(t_all *all)
{
	char *command;

	if (is_prefix_bin(all->command_argv[0]))
		return all->command_argv[0];
	else
	{
		command = ft_strjoin("/bin/", all->command_argv[0]);
	}
//	printf("command = %s\n", command);
	return (command);
}

/*!
** \author fgrisell
**
*/
void bin_func(t_all *all, char **env)
{
	int status;
	char *command;
	char *error;

	pid_t pid = fork();
	if (pid < 0)
		ft_putendl_fd(strerror(errno), 2);
	if (pid == 0)
	{
		command = check_bin_func(all);
		status = execve(command, all->command_argv, env);
/*		if (status == -1)
		{
			char *temp = all->command_argv[0];
			all->command_argv[0] = ft_strjoin(all->command_argv[0], ": ");
			free(temp);
			error = ft_strjoin(all->command_argv[0], strerror(errno));
			ft_putendl_fd(error, 2);
			free(error);
		}*/
		printf("CHILD status : %d\n", status);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);// waitpid(-1, &status, 0); == wait(&status);
//		printf(RED"WEXITSTATUS = %d\n", WEXITSTATUS(status));
//		printf(END);
		if (WIFEXITED(status) != 0)
		{
			printf("PARENT : успешно: \n");
			printf("status = %d\n", WEXITSTATUS(status));
//
//			exit(status);
		}
		else
		{
			printf("status = %d\n", WEXITSTATUS(status));
			if (WEXITSTATUS(status) == -1)
			{

				char *temp = all->command_argv[0];
				all->command_argv[0] = ft_strjoin(all->command_argv[0], ": ");
				free(temp);
				error = ft_strjoin(all->command_argv[0], strerror(errno));
				ft_putendl_fd(error, 2);
				free(error);
			}

			printf("PARENT : не успешно: \n");
			printf("status = %d\n", WEXITSTATUS(status));
//			exit(status);
		}
//		if (WEXITSTATUS(status) == 0)
//			return;
/*		else
		{
			error = ft_strjoin(all->command_argv[0], strerror(errno));
			ft_putendl_fd(error, 2);
			free(error);
		}*/
//		if (WIFEXITED(status))
//		printf("Выполнено успешно!\n");
	}
}
