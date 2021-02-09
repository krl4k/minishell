/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:59:05 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/04 20:59:07 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** "<" input redirect
*/

int		input_redir_init(t_all *all, int index)
{
	if ((index == 0) && (all->input_redir_flag == 1))
	{
		if ((all->input_file_descriptor = open(all->in_path, O_RDONLY)) < 0)
			ft_perror("open()");
		if (all->input_file_descriptor == -1)
		{
			ft_perror("input file failed to open\n");
			return (EXIT_FAILURE);
		}
		close(READ);
		dup(all->input_file_descriptor);
		close(all->input_file_descriptor);
	}
	return (EXIT_SUCCESS);
}

/*
** ">" output redirect
*/

int		output_redir_init(t_all *all, int index)
{
	if ((all->output_file_descriptor = open(all->out_path, O_WRONLY
	| O_TRUNC | O_CREAT, 0644)) < 0)
		ft_perror("open()");
	if (all->output_file_descriptor < 0)
	{
		ft_perror("output file failed to open\n");
		return (EXIT_FAILURE);
	}
	close(WRITE);
	dup(all->output_file_descriptor);
	close(all->output_file_descriptor);
	return (EXIT_SUCCESS);
}

/*
** ">>" output & append redirect
*/

int		append_redir_init(t_all *all, int index)
{
	if ((all->output_file_descriptor = open(all->out_path,
	O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
	{
		ft_perror("open()");
		return (EXIT_FAILURE);
	}
	if (all->output_file_descriptor < 0)
	{
		ft_perror("output file failed to open");
		return (EXIT_FAILURE);
	}
	close(WRITE);
	dup(all->output_file_descriptor);
	close(all->output_file_descriptor);
	return (EXIT_SUCCESS);
}

void	pipes_fd_init(t_all *all, int index)
{
	if (index == 0)
	{
		close(WRITE);
		dup(all->r_pipe[WRITE]);
		close(all->r_pipe[WRITE]);
		close(all->r_pipe[READ]);
	}
	else if (index < all->pipes)
	{
		close(READ);
		dup(all->l_pipe[READ]);
		close(all->l_pipe[READ]);
		close(all->l_pipe[WRITE]);
		close(WRITE);
		dup(all->r_pipe[WRITE]);
		close(all->r_pipe[READ]);
		close(all->r_pipe[WRITE]);
	}
	else
	{
		close(READ);
		dup(all->l_pipe[READ]);
		close(all->l_pipe[READ]);
		close(all->l_pipe[WRITE]);
	}
}
