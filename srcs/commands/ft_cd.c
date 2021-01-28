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

static char *home(t_all *all)
{
//	printf("home================\n");
	int i;

	i = 0;
	while (all->env_array->str[i])
	{
		if (ft_strncmp(all->env_array->str[i], "HOME=", 5) == 0)
			return (&all->env_array->str[i][5]);
		i++;
	}
	return ("NULL");
}

static void find_home(t_all *all)
{

}

int ft_cd(t_all *all)
{
	char *h;

	if (!all->command_argv[1])
	{
		if ((ft_strncmp("NULL", h = home(all), 4)) == 0)
		{
			ft_putstr_fd(PROMT_ERROR, 2);
			ft_putstr_fd(all->command_argv[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd("HOME not set", 2);
			return (0);
		}
		else
			all->command_argv[1] = h;
	}
	else if (ft_strncmp(all->command_argv[1], "~", 1) == 0)
		all->command_argv[1] = all->old_home;
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