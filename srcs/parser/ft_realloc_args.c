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

int		size_arr(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

char **ft_realloc_args(char **p, int new_size)
{
	int i;
	int size;
	char **new;

	if (!(new = (char **)ft_calloc(sizeof(char *), (new_size + 1))))
		return (NULL);
	i = 0;
	size = size_arr(p);
	while (i < size)
	{
		if (!(new[i] = ft_strdup(p[i])))
		{
			ft_free_split(p);
			ft_free_split(new);
			return (NULL);
		}
		i++;
	}
	ft_free_split(p);
	return (new);
}