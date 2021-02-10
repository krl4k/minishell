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

void execute_child_proc(t_all *all, char *command, int status)
{
	g_exit_code = 1;
	status = execve(command, all->command_argv, all->env_array->str);
	if (status == -1)
	{
//		printf("govna poel\n");
		exit(127);
	}
	free(command);
	exit(status);
}

static void check_error(char *command)
{
	int i;
	int count_slash;

	count_slash = 1;
	i = 0;
	if (!command)
		return;
	while (command[i])
	{

	}
}

void print_error(t_all *all)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd(all->command_argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("command not found", 2);
}

void execute_parent_proc(t_all *all, int status, pid_t pid)
{
	g_exit_code = 1;
	if (WIFEXITED(status) != 0)
	{
		g_exit_code = 0;
		if (WEXITSTATUS(status) == 127)
		{
			g_exit_code = 127;
			print_error(all);
		}
	}
}

//!todo stat, check file: file or dir?
int execute(t_all *all)
{
	int		status;
	char	*command;
	pid_t	pid;

	signals_init(2);
	all->env_array->str[all->env_array->current_size] = NULL;
	command = check_bin_func(all, all->command_argv[0]);
	if ((pid = fork()) < 0)
		ft_perror("fork()");
	if (pid == 0)
		execute_child_proc(all, command, status);
	else
	{
		waitpid(pid, &status, 0);
		execute_parent_proc(all, status, 0);
		if (command)
			free(command);
	}
//	if (command)
//		free(command);
//	bin_func(all);
	return (EXIT_SUCCESS);
}