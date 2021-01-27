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

static char **sort_vars(char **env, int count)
{
	int i;
	int	sorted;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < count - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])))
			{

			}
		}
	}
}

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


	while ()
}