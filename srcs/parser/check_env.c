/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:39:09 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_env(t_all *all)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (all->tmp[i])
	{
		j = 0;
		while (all->tmp[i][j])
		{
			if (all->tmp[i][j] == '$')
			{
				tmp = all->tmp[i];
				all->tmp[i][j++] = '\0';
				all->tmp[i] = ft_strjoin(all->tmp[i], get_env_by_key(all, &all->tmp[i][j]));
				free(tmp);
			}
			j++;
		}
		i++;
	}
}

