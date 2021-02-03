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

static void error_mes(char *command)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
}

int check_valid(char *key)
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

int is_same_key(t_all *all, char *new_key)
{
	int i;

	i = 0;
	while (i < all->env_array->current_size)
	{
		if (ft_is_equal(all->env_array->key[i], new_key))
		{
			printf("same key!!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int check_valid_key(t_all *all, char *new_env)
{
	int i;
	char *new_key;
	char *new_value;
	int ret_v;
	i = 0;

	ret_v = 0;
	while (new_env[i] && new_env[i] != '=')
		i++;
	new_key = ft_substr(new_env, 0, i);
	new_value = ft_substr(new_env, i + 1, ft_strlen(new_env));
//	printf("new_env     = |%s|\n", new_env);
//	printf("new key     = |%s|\n", new_key);
//	printf("new value   = |%s|\n", new_value);
//	printf("new_env[%d] = |%c|\n", i, new_env[i]);
//	printf("strlen      =|%zu|\n", ft_strlen(new_env));
//	printf("i + 1       = |%d|\n", i + 1);
	if (!check_valid(new_key))
		ret_v = 1;
	if (new_env[i] == '\0' && !is_same_key(all, new_key))
		ret_v = 2;
	if (new_env[i] == '=')
		ret_v = 0;
//	if (!is_same_key(new_key))
//		ret_v = 0;
//	if (check_same_value)
//	if (check_same_value(new_key))
//	if (!new_value)// && new_env[i] != '='
//		return (2);
//	if (i + 1 > ft_strlen(new_env))
//		return (2);
	while (ret_v == 0 && i < all->env_array->current_size)
	{
		if (ft_is_equal(all->env_array->key[i], new_key))
		{
			printf("all->env->key[i] = |%s|\n", all->env_array->key[i]);
			printf("new key    		 = |%s|\n", new_key);
			all->env_array->delete_one_by_key(all->env_array, all->env_array->key[i]);
		}
		i++;
	}
	free(new_key);
	free(new_value);
	return (ret_v);
}


void add_env(t_all *all, int count)
{
	int i;
	int check;

	check = 0;
	i = 1;

	printf("envs = \n");
	for (int j = 0; all->command_argv[j]; ++j)
	{
		printf("env[%d] = |%s|\n", j, all->command_argv[j]);
	}
	while (all->command_argv[i])
	{
		if(all->command_argv[i][0] == '=')
			error_mes(all->command_argv[i]);
		else
		{
			printf("pushback = %s\n", all->command_argv[i]);
			check = check_valid_key(all, all->command_argv[i]);
			if (check == 0)
			{
				all->env_array->push_back(all->env_array, all->command_argv[i]);
			}
			else if(check == 1)
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

	printf("ft_export start \n");
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