/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:28:14 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/28 10:28:16 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_mes(char *command)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
}


//\todocheck first arg
int		check_valid_argv(char *key)
{
	int i;

	i = 0;
	if (ft_isdigit(key[i]) != 0)
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) || ft_strrchr("!@#$:%^&*-+?={}~`[]/,.",
		key[i]) != NULL)
			return (0);
		i++;
	}
	return (1);
}

/*
** \author fgrisell
** removes an element from the environment variable by key
*/

int		ft_unset(t_all *all)
{
	int i;
	int j;

	i = 1;
	while (all->command_argv[i])
	{
		j = 0;
		if (!check_valid_argv(all->command_argv[i]))
			error_mes(all->command_argv[i]);
		while (all->env_array->str[j])
		{
			if (ft_strcmp(all->env_array->key[j], "OLDPWD") == 0)
			{
				free(all->old_pwd);
				all->old_pwd = NULL;
			}
			if (ft_strcmp(all->env_array->key[j], all->command_argv[i]) == 0)
				all->env_array->delete_one_by_key(all->env_array,
				all->command_argv[i]);
			j++;
		}
		i++;
	}
	return (0);
}
