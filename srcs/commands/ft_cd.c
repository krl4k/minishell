/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:00:41 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 15:00:42 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_home(t_all *all)
{
	int i;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], "HOME=", 5) == 0)
			return (all->env[i]);

	}
}

int ft_cd(t_all *all)
{
	if (!all->command_argv[1] || ft_strncmp(all->command_argv[1], "~", 1) == 0)
	{
		//if ()
	}
	if ((chdir(all->command_argv[1])) == -1)
	{
		ft_putstr_fd(PROMT_ERROR, 2);
		ft_putstr_fd(all->command_argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(all->command_argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (0);
}