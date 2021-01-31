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
	int i;

	init_array(&all->env_array, 1);
//	init_array(&all->env_array, 1);
//	printf("start env init\n");
	i = 0;
	while (env[i])
	{
		all->env_array->push_back(all->env_array, env[i]);
		if (ft_strncmp(env[i],"HOME=", 5) == 0)
			all->old_home = ft_strdup(&env[i][5]);
//		printf("env[%d] = %s\n", i, env[i]);
//		printf("key[%d] = %s , ",i, all->env_array->key[i]);
//		printf("val[%d] = %s\n",i, all->env_array->value[i]);
		i++;
	}
//	printf("env inited\n");
//	all->env_array->print_array(all->env_array);
}

void init_all(t_all **all, char **env)
{
	if (!(*all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
	(*all)->c_bin_command = 0;
	init_env(*all, env);
}
