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

static int ft_strlen_set(char *str, char *set)
{
	int i;

	i = 0;
	while (!ft_strchr(set, *str) && *str)
	{
		if (*str == '\\')
		{
			str++;
			continue;
		}
		str++;
		i++;
	}
	return (i);
}
char *get_word(char *line, int *i)
{
	char	*res;
	int		size;
	int		k;
	int 	j;

	j = *i;
	k = 0;
	if (!(size = ft_strlen_set(&line[j], "\'\" <>|;")))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (!ft_strchr("\'\" <>|;", line[j]) && line[j])
	{
		if (line[j] == '\\')
		{
			j++;
			continue;
		}
		res[k++] = line[j++];
	}
	res[k] = '\0';
	*i = j;
	return (res);
}

