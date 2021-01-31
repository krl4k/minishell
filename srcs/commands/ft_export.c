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
//
//static void sort_vars(char **env, int count)
//{
//	int i;
//	int sorted;
//	char *temp;
//
//	sorted = 0;
//	while (!sorted)
//	{
//		i = 0;
//		sorted = 1;
//		while (i < count - 1)
//		{
//			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
//			{
//				temp = env[i];
//				env[i] = env[i + 1];
//				env[i + 1] = temp;
//				sorted = 0;
//			}
//			i++;
//		}
//	}
//}


static void sort_vars(char **env, int count, int *index)
{
	int i;
	int sorted;
	int temp;
	char *tmp;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < count - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = index[i];
				index[i] = index[i + 1];
				index[i + 1] = temp;
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

static int count_command(t_all *all)
{
	int i;

	i = 0;
	while (all->command_argv[i])
	{
		i++;
	}
	return (i);
}

static void error_mes(char *command, char *new)
{
	ft_putstr_fd(PROMT_ERROR, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
}


static void add_one(t_all *all, char ***new_array, int pos, char *new)
{
	int i;

	i = 0;
	printf("add one\n");
	while (new[i])
	{
		if (new[i] == '=')
			break;
		i++;
	}
	if (i > 0)
	{
		printf("i > 0 i = %c|\n", new[i]);
		if (new[i - 1] == ' ')
		{
			printf("i - 1\n");
			error_mes(all->command_argv[1], new);
		}
	} else
		error_mes(all->command_argv[1], new);
//		(*new_array)[pos];
	*new_array[pos] = ft_strdup(new);
}

void add_env(t_all *all)
{

}

/*!
** \attention function add env or show all env if export with zero arg
** \example export x=123
** \example export x="     123"
** \example export x= 123 (env x="", env 123)
** \todo add env
*/

void write_export(t_array *array, int i)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(array->key[i], 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(array->value[i], 1);
	ft_putendl_fd("\"", 1);
}


void print_sort_envs(t_all *all, char **temp_env, int *env_index)
{
	int i;

	i = 0;
	while (all->env_array->str[i])
	{
		temp_env[i] = ft_strdup(all->env_array->str[i]);
		i++;
	}
	temp_env[i] = NULL;
	i = 0;
	while (i < all->env_array->current_size)
	{
		env_index[i] = i;
		i++;
	}
	sort_vars(temp_env, all->env_array->current_size, env_index);
	i = 0;
	while (i < all->env_array->current_size)
	{
		write_export(all->env_array, env_index[i]);
		i++;
	}
}


int ft_export(t_all *all)
{
	char **temp_env;
	int *env_index;
	int i;
	int count;

	i = 0;
	if ((count = count_command(all)) != 1)
	{
		add_env(all);
		return (0);
	}
	else
	{
		if (!(temp_env = (char **) malloc((all->env_array->current_size) * sizeof(char *)))
			|| !(env_index = (int *) ft_calloc(all->env_array->current_size, sizeof(int))))
			error_handler(1);
		print_sort_envs(all, temp_env, env_index);
		while (i < all->env_array->current_size && temp_env[i])
		{
			free(temp_env[i++]);
		}
		free(temp_env);
		free(env_index);
	}
	return (0);
}