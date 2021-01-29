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

	i = 0;
	while (env[i])
	{
		all->env_array->push_back(all->env_array, env[i]);
		if (ft_strncmp(env[i],"HOME=", 5) == 0)
			all->old_home = ft_strdup(&env[i][5]);
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
