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

char *home(t_all *all)
{
	int i;

	i = 0;
	while (all->env_array->str[i])
	{
		if (ft_strcmp(all->env_array->key[i], "HOME") == 0)
		{
			return (ft_strdup(all->env_array->value[i]));
		}
		i++;
	}
	return (ft_strdup("NULL"));
}

void 	save_oldpwd(t_all *all)
{
	int i;
	char *old_pwd;
	char *temp;

	i = 0;
	temp = NULL;
	if (!(old_pwd = getcwd(NULL, 0)))
		return;
	while (i < all->env_array->current_size)
	{
		if (ft_is_equal("OLDPWD", all->env_array->key[i]))
			all->env_array->delete_one_by_key(all->env_array, "OLDPWD");
		temp = ft_strjoin("OLDPWD=",old_pwd);
		if (all->old_pwd)
			free(all->old_pwd);
		all->old_pwd = ft_strdup(old_pwd);
		all->env_array->push_back(all->env_array, temp);
		free(temp);
		i++;
	}
	free(old_pwd);
}

int ft_cd(t_all *all)
{
	char *h;

	h = NULL;
	if (!all->command_argv[1])
	{
		if (not_path_cd(all, &h) == 0)
			return (0);
	}
	else if (ft_strncmp(all->command_argv[1], "~", ft_strlen(all->command_argv[1])) == 0)
	{
		free(all->command_argv[1]);
		all->command_argv[1] = ft_strdup(all->old_home);
	}
	else if (ft_strncmp(all->command_argv[1], "-", ft_strlen(all->command_argv[1])) == 0)
	{
		free(all->command_argv[1]);
		all->command_argv[1] = ft_strdup(all->old_pwd);
		if (!all->command_argv[1])
		{
			oldpwd_not_set(all);
			return (0);
		}
		ft_putendl_fd(all->old_pwd, 1);
	}
	save_oldpwd(all);
	if ((chdir(all->command_argv[1])) == -1)
		chdir_error(all);
//	new_oldpwd(all);
	free(h);
	return (0);
}