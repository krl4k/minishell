/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/12 20:31:11 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		shell_lvl(char *env_lvl)
{
	int		i;
	int		lvl;
	char	*new_lvl;

	i = 0;
	while (env_lvl[i] && env_lvl[i] != '=')
		i++;
	i++;
	if (env_lvl[i])
	{
		lvl = ft_atoi(&env_lvl[i]);
		lvl++;
		new_lvl = ft_itoa(lvl);
		ft_memcpy(&env_lvl[i], new_lvl, ft_strlen(new_lvl));
		free(new_lvl);
	}
}

static void		init_env(t_all *all, char **env)
{
	int i;

	i = 0;
	init_array(&all->env_array, 40);
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			shell_lvl(env[i]);
		all->env_array->push_back(all->env_array, env[i]);
		if (ft_strcmp(all->env_array->key[i], "HOME") == 0)
		{
			all->old_home = ft_strdup(all->env_array->value[i]);
		}
		if (ft_strcmp("PATH", all->env_array->key[i]) == 0)
		{
			if (!(all->old_path = ft_split(all->env_array->value[i], ':')))
				exit(12);
		}
		if (ft_strcmp("OLDPWD", all->env_array->key[i]) == 0)
		{
			if (!(all->old_pwd = ft_strdup(all->env_array->key[i])))
				return ;
		}
		i++;
	}
}

void			init_all(t_all **all, char **env)
{
	if (!(*all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
	init_env(*all, env);
}
