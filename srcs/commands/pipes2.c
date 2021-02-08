/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:55:35 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/04 20:55:36 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proccess(t_all *all, int index)
{
	char	*command;

	if ((index == 0) && (all->input_redir_flag == 1))
		input_redir_init(all, index);
	if ((index == all->pipes) && (all->output_redir_flag == 1))
		output_redir_init(all, index);
	if ((index == all->pipes) && (all->append_redir_flag == 1))
		append_redir_init(all, index);
	if (all->pipes > 0)
		pipes_fd_init(all, index);
	command = check_bin_func(all->command_argv[all->arg_location[index]]);
	if (!command)
		exit(3);
	all->status = execve(command, &all->command_argv[all->arg_location[index]],
		all->env_array->str);
	if (command)
		free(command);
	ft_perror(command);
	exit(all->status);
}

void	parent_proccess(t_all *all, int index)
{
	if (index > 0)
	{
		close(all->l_pipe[READ]);
		close(all->l_pipe[WRITE]);
	}
	all->l_pipe[READ] = all->r_pipe[READ];
	all->l_pipe[WRITE] = all->r_pipe[WRITE];
	wait(&all->status);
	if (WIFEXITED(all->status) != 0)
	{
		if (WEXITSTATUS(all->status) == 3)
		{
			ft_putstr_fd(PROMT_ERROR, 2);
			ft_putstr_fd(all->command_argv[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("command not found", 2);
		}
	}
}

int		execute_commands(t_all *all)
{
	int		index;
	pid_t	pid;

	index = 0;
	while (index <= all->pipes)
	{
		if (all->pipes > 0 && index != all->pipes)
			if (pipe(all->r_pipe) < 0)
				ft_perror("pipe() error");
		if ((pid = fork()) < 0)
			ft_perror("fork() error");
		if (pid == 0)
			child_proccess(all, index);
		else
			parent_proccess(all, index);
		index++;
	}
	return (EXIT_SUCCESS);
}

/*
** redir management
*/

void	check_flags(t_all *all)
{
	int count;

	count = 0;
	while (all->command_argv[count])
	{
		if (ft_strcmp(all->command_argv[count], "|") == 0)
		{
			all->command_argv[count] = 0;
			all->arg_location[all->pipes + 1] = count + 1;
			++(all->pipes);
		}
		else if (ft_strcmp(all->command_argv[count], "<") == 0)
			set_flags(all, &all->in_path, &all->input_redir_flag, count);
		else if (ft_strcmp(all->command_argv[count], ">") == 0)
			set_flags(all, &all->out_path, &all->output_redir_flag, count);
		else if (ft_strcmp(all->command_argv[count], ">>") == 0)
			set_flags(all, &all->out_path, &all->append_redir_flag, count);
		else
			all->arg_location[count] = count;
		++count;
	}
}

int		pipes_work(t_all *all)
{
	init_handler_pipes(all);
	check_flags(all);
	execute_commands(all);
	free_handler_pipes(all);
	return (0);
}