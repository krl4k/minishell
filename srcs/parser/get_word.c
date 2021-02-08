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

static int ft_strlen_set(const char *str, const char *set)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (!ft_strchr(set, str[k]) && str[k])
	{
		if (str[k] == '\\')
		{
			k++;
			continue;
		}
		k++;
		i++;
	}
	return (i);
}

char *get_word(char *line, t_all *all)
{
	char	*res;
	int		size;
	int		k;

	k = 0;
	if (!(size = ft_strlen_set(&line[all->i], "\'\" <>|;")))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (k < size)
	{
		if (ft_strchr("\\", line[all->i]))
		{
			all->i++;
			continue;
		}
		res[k++] = line[all->i++];
	}
	res[k] = '\0';
	return (res);
}

