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

static void sort_vars(char **env, int count)
{
	int i;
	int	sorted;
	char *temp;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < count - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}

static int count_env(t_all * all)
{
	int i;

	i = 0;
	while (all->env[i])
	{
		i++;
	}
	return (i);
}
/*!
** \attention function add env or show all env if export with zero arg
** \example export x=123
** \example export x= 123
** \example export x="     123"
** \example export x= 123 (env x="", env 123)
** \todo add env
*/
int ft_export(t_all *all)
{
	char **temp_env;
	int i;

	i = 0;
	if (!(temp_env = (char **)malloc((all->env_count + 1) * sizeof(char *))))
		exit(0);
	while (all->env[i])
	{
		temp_env[i] = ft_strdup(all->env[i]);
		i++;
	}
	temp_env[i] = NULL;
	sort_vars(temp_env, all->env_count);
	i = 0;
	while (temp_env[i])
	{
		ft_putendl_fd(temp_env[i], 1);
		i++;
	}
	i = 0;
	while (temp_env[i])
		free(temp_env[i++]);
	free(temp_env);
	return (0);
}