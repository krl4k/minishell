/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/13 20:36:51 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env(t_all *all)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (all->command_argv[i])
	{
		j = 0;
		while (all->command_argv[i][j])
		{
			if (all->command_argv[i][j] == '$' &&
				all->command_argv[i][j - 1] != '\\')
			{
				tmp = all->command_argv[i];
				all->command_argv[i][j++] = '\0';
				all->command_argv[i] = ft_strjoin(all->command_argv[i],
						get_env_by_key(all, &all->command_argv[i][j]));
				free(tmp);
			}
			j++;
		}
		i++;
	}
}
