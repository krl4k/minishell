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
	free(all->command_argv[count]);
	all->command_argv[count] = 0;
	*path = ft_strdup(all->command_argv[count + 1]);
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
		exit(2);
}

void	free_handler_pipes(t_all *all)
{
	if (all->in_path)
		free(all->in_path);
	if (all->out_path)
		free(all->out_path);
	if (all->arg_location)
		free(all->arg_location);
}
