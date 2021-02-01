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

static int count_command(t_all *all)
{
	int i;

	i = 0;
	while (all->command_argv[i])
		i++;
//	printf("count commnd = %d\n", i);
	return (i);
}

static void error_mes(char *command)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
}

int check_valid_key(char *key)
{
	int i;

	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) || ft_strrchr("!@#$%^&*-+", key[i]) != NULL)
		{
//			printf("check valid key[%d] = %c\n", i, key[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
int check_same_key(t_all *all, char *new_env)
{
	int i;
	char *new_key;

	i = 0;
	while (new_env[i] && new_env[i] != '=')
		i++;
	if (new_env[i] == '\0')
		new_key = ft_strdup(new_env);
	else
		new_key = ft_substr(new_env, 0, i);
	if (!check_valid_key(new_key))
	{
		return (1);
	}
	printf("new_env = %s\n", new_env);
	printf("new key = %s\n", new_key);
	printf("new value = %s\n", &new_env[i + 1]);
	printf("strlen new-env = %zu\n", ft_strlen(new_env));
	printf("i + 1 = %d\n", i + 1);
	i = 0;
	if (i + 1 > ft_strlen(new_env) || new_env[i + 1] == '\0')
		return (2);
	while (i < all->env_array->current_size)
	{
		if (ft_strncmp(all->env_array->key[i], new_key, ft_strlen(all->env_array->key[i])))
		{
			all->env_array->delete_one_by_key(all->env_array, new_key);
		}
		i++;
	}
	free(new_key);
	return (0);
}


void add_env(t_all *all, int count)
{
	int i;
	int check_same;

	check_same = 0;
	i = 1;
	while (all->command_argv[i])
	{
		if(all->command_argv[i][0] == '=')
			error_mes(all->command_argv[i]);
		else
		{
//			printf("pushback = %s\n", all->command_argv[i]);
			check_same = check_same_key(all, all->command_argv[i]);
			if (check_same == 0)
			{
				all->env_array->push_back(all->env_array, all->command_argv[i]);
			}
			else if(check_same == 1)
				error_mes(all->command_argv[i]);
			else
				;
		}
		i++;
	}

}

/*!
** \attention function add env or show all env if export with zero arg
** \example export x=123
** \example export x="     123"
** \example export x= 123 (env x="", env 123)
** \todo add env
*/


int ft_export(t_all *all)
{

	int count;

//	printf("ft_export start \n");
	if((count = count_command(all)) != 1)
	{
//		printf("count env = %d\n", count);
		add_env(all, count - 1);
		return (0);
	}
	else
	{
		ft_export_print_sort_env(all);
	}
	return (0);
}