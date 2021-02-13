/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:34:47 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/13 13:34:49 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_zero(t_all *all, int i)
{
	all->env_array->push_back(all->env_array, all->command_argv[i]);
	if (ft_strncmp(all->command_argv[i], "HOME=", 5) == 0)
	{
		free(all->old_home);
		all->old_home = ft_strdup(&all->command_argv[i][5]);
	}
	if (ft_strncmp(all->command_argv[i], "OLDPWD=", 7) == 0)
	{
		if (all->old_pwd)
			free(all->old_pwd);
		all->old_pwd = ft_strdup(&all->command_argv[i][7]);
	}
}
