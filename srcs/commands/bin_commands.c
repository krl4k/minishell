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
	return (command);
}

/*!
** \author fgrisell
**
*/
void bin_func(t_all *all)
{
	int		status;
	char	*command;
	pid_t	pid;

	if ((pid = fork()) < 0)
		ft_putendl_fd(strerror(errno), 2);
	if (pid == 0)
	{
		command = check_bin_func(all);
		status = execve(command, all->command_argv, all->env);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);// waitpid(-1, &status, 0); == wait(&status);
		if (WIFEXITED(status) != 0)
		{
			if (WEXITSTATUS(status) != 0)
			{
				ft_putstr_fd(PROMT_ERROR, 2);
				ft_putstr_fd(all->command_argv[0], 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd("command not found", 2);
			}
		}
	}
}
