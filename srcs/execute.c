/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:51:13 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/12 20:34:24 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		execute_child_proc(t_all *all, char *command, int status)
{
	status = execve(command, all->command_argv, all->env_array->str);
	if (status == -1)
		exit(127);
	free(command);
	exit(status);
}

static int	is_directory_or_file(char *command)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	if (!command)
		return (0);
	if (command[i] == '/')
	{
		flag = 1;
		i++;
	}
	while (command[i] && command[i] == '/' && command[i] == '.')
		i++;
	if (i == 1)
		return (1);
	if (flag == 0)
		return (0);
	return (1);
}

void		print_error(t_all *all)
{
	struct stat s;

	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd(all->command_argv[0], 2);
	ft_putstr_fd(": ", 2);
	stat(all->command_argv[0], &s);
	if (S_ISDIR(s.st_mode))
	{
		g_exit_code = 126;
		ft_putendl_fd("is a directory", 2);
	}
	else if (S_ISREG(s.st_mode))
	{
		g_exit_code = 126;
		ft_putendl_fd("Permission denied", 2);
	}
	else if (is_directory_or_file(all->command_argv[0]))
	{
		g_exit_code = 127;
		ft_putendl_fd("No such file or directory", 2);
	}
	else
	{
		g_exit_code = 127;
		ft_putendl_fd("command not found", 2);
	}
}

void		execute_parent_proc(t_all *all, int status)
{
	if (status == 0)
	{
		g_exit_code = 0;
		return ;
	}
	if (WIFEXITED(status) != 0)
	{
		g_exit_code = 1;
		if (WEXITSTATUS(status) == 127)
		{
			g_exit_code = 1;
			print_error(all);
		}
	}
}

int			execute(t_all *all)
{
	int		status;
	char	*command;
	pid_t	pid;

	status = 0;
	signals_init(2);
	g_exit_code = 0;
	all->env_array->str[all->env_array->current_size] = NULL;
	command = check_bin_func(all, all->command_argv[0]);
	if ((pid = fork()) < 0)
		ft_perror("fork()");
	if (pid == 0)
		execute_child_proc(all, command, status);
	else
	{
		waitpid(pid, &status, 0);
		execute_parent_proc(all, status);
		if (command)
			free(command);
	}
	return (EXIT_SUCCESS);
}
