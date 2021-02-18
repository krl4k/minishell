/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:20:20 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/05 16:20:22 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flags(t_all *all, char **path, int *flag, int count)
{
	int fd;

	*path = ft_strdup(all->command_argv[count + 1]);
	if (ft_is_equal(all->command_argv[count], "<"))
		all->count_redir--;
	if (ft_is_equal(all->command_argv[count], ">")
	|| (ft_is_equal(all->command_argv[count], ">>")))
	{
		if ((fd = open(*path, O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
			exit(EXIT_FAILURE);
		close(fd);
		all->count_redir--;
	}
	if (all->count_redir > 0)
	{
		if (all->count_redir > 0)
			free(*path);
	}
	free(all->command_argv[count + 1]);
	free(all->command_argv[count]);
	all->command_argv[count + 1] = ft_strdup("wp");
	all->command_argv[count] = 0;
	*flag = 1;
}

void	init_handler_pipes(t_all *all)
{
	all->in_path = NULL;
	all->out_path = NULL;
	all->input_redir_flag = 0;
	all->output_redir_flag = 0;
	all->append_redir_flag = 0;
	all->pipes = 0;
	if (!(all->arg_location = (int *)malloc(sizeof(int) * count_command(all))))
		exit(12);
}

void	free_handler_pipes(t_all *all)
{
	if (all->in_path)
	{
		free(all->in_path);
		all->in_path = NULL;
	}
	if (all->out_path)
	{
		free(all->out_path);
		all->out_path = NULL;
	}
	if (all->arg_location)
		free(all->arg_location);
}

void	count_redir(t_all *all)
{
	int i;

	i = 0;
	all->count_redir = 0;
	while (all->command_argv[i])
	{
		if (ft_is_equal(all->command_argv[i], ">")
		|| ft_is_equal(all->command_argv[i], ">>"))
			all->count_redir++;
		i++;
	}
}
