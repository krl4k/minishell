/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:29:25 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 18:29:26 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_command(t_all *all)
{
	int i;

	i = 0;
	while (all->command_argv[i])
		i++;
	return (i);
}

/*
** \return 0 if the environment variables have the same key, there is the same key
** \else 1
*/

int is_same_key(t_all *all, char *new_key)
{
	int i;

	i = 0;
	while (i < all->env_array->current_size)
	{
		if (ft_is_equal(all->env_array->key[i], new_key))
			return (0);
		i++;
	}
	return (1);
}

int check_valid_key(t_all *all, char *new_env)
{
	int		i;
	char	*new_key;
	char	*new_value;
	int		ret_v;

	i = 0;
	ret_v = 0;
	while (new_env[i] && new_env[i] != '=')
		i++;
	new_key = ft_substr(new_env, 0, i);
	new_value = ft_substr(new_env, i + 1, ft_strlen(new_env));
	if (!check_valid_argv(new_key))
		ret_v = 1;
	if (new_env[i] == '\0' && !is_same_key(all, new_key))
		ret_v = 2;
	if (new_env[i] == '=')
		ret_v = 0;
	while (ret_v == 0 && i < all->env_array->current_size)
	{
		if (ft_is_equal(all->env_array->key[i], new_key))
			all->env_array->delete_one_by_key(all->env_array, all->env_array->key[i]);
		i++;
	}
	free(new_key);
	free(new_value);
	return (ret_v);
}

/*
** printf("all->env->key[i] = |%s|\n", all->env_array->key[i]);
** printf("new key    		 = |%s|\n", new_key);
*/

/*
** 	printf("envs = \n");
**	for (int j = 0; all->command_argv[j]; ++j)
**	{
**		printf("env[%d] = |%s|\n", j, all->command_argv[j]);
**	}
*/

void	add_env(t_all *all)
{
	int	i;
	int	check;

	i = 1;
	while (all->command_argv[i])
	{
		if (all->command_argv[i][0] == '=')
			error_mes(all->command_argv[i]);
		else
		{
			check = check_valid_key(all, all->command_argv[i]);
			if (check == 0)
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
			else if (check == 1)
				error_mes(all->command_argv[i]);
			else
				;
		}
		i++;
	}
}

/*
** \attention function add env or show all env if export with zero arg
** \example export x=123
** \example export x="     123"
** \example export x= 123 (env x="", env 123)
*/

int		ft_export(t_all *all)
{
	int count;

	count = 0;
	if ((count = count_command(all)) != 1)
	{
		add_env(all);
		return (0);
	}
	else
		ft_export_print_sort_env(all);
	return (0);
}
