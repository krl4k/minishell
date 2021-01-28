/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 13:42:07 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_env(t_all *all, char **env)
{
	int count;
	int i;

	count = 0;
	printf("all\n");
	while (env[count])
		count++;
	if (!(all->env = (char **) malloc((count + 1) * sizeof(char *))))
		exit(0);
	all->env_count = count;
//	printf("count = %d\n", all->env_count);
//	printf("init env = %s\n", env[0]);
	i = 0;
	while (env[i])
	{
//		printf("env = %s\n", env[i]);
		if (ft_strncmp(env[i],"HOME=", 5) == 0)
			all->old_home = ft_strdup(&env[i][5]);
		all->env[i] = ft_strdup(env[i]);
		i++;
	}
//	printf("env[last] = %s\n", all->env[0]);
	all->env[i] = NULL;
}

void init_all(t_all **all, char **env)
{
	if (!(*all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
	(*all)->c_bin_command = 0;
	init_env(*all, env);
}
