/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:23:33 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/05 18:23:34 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		print_prompt(1);
		signal(SIGINT, ctrl_c);
	}
}

static void	ctrl_c_cat(int sig_num)
{
//	if (sig_num == SIGINT)
	(void)sig_num;
	{
		write(1, "\n", 1);
		g_exit_code = 130;
		signal(SIGINT, ctrl_c_cat);
	}
}

static void	ctrl_slash(int fork)
{
	if (fork == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		signal(SIGQUIT, ctrl_slash);
	}
}

static void	ctrl_slash_cat(int fork)
{
	(void)fork;
//	if (fork == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "^\\Quit: 3\n", 10);
		g_exit_code = 131;
		signal(SIGQUIT, ctrl_slash_cat);
	}
}

void		signals_init(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
	}
	if (mode == 2)
	{
		signal(SIGINT, ctrl_c_cat);
		signal(SIGQUIT, ctrl_slash_cat);
	}
}
