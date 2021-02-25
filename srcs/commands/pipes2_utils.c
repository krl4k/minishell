/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:55:35 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/25 11:23:46 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_check_flags(t_all *all, int count)
{
	if (ft_strcmp(all->command_argv[count], "<") == 0)
	{
		if (set_flags(all, &all->in_path, &all->input_redir_flag, count) == 1)
			return (0);
	}
	else if (ft_strcmp(all->command_argv[count], ">") == 0)
	{
		if (set_flags(all, &all->out_path, &all->output_redir_flag, count) == 1)
			return (0);
	}
	else if (ft_strcmp(all->command_argv[count], ">>") == 0)
	{
		if (set_flags(all, &all->out_path, &all->append_redir_flag, count) == 1)
			return (0);
	}
	return (1);
}
