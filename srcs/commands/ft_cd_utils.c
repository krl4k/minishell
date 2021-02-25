/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:53:49 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/25 11:25:56 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chdir_error(t_all *all)
{
	g_exit_code = 1;
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd(all->command_argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(all->command_argv[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void	home_not_set(t_all *all, char **h)
{
	(void)h;
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd(all->command_argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("HOME not set", 2);
}

void	oldpwd_not_set(t_all *all)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd(all->command_argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("OLDPWD not set", 2);
}

int		not_path_cd(t_all *all, char **h)
{
	if (!(*h = home(all)))
		home_not_set(all, h);
	else
	{
		save_oldpwd(all);
		if ((chdir(*h)) == -1)
			chdir_error(all);
		new_pwd(all);
		if (*h)
			free(*h);
	}
	return (0);
}
