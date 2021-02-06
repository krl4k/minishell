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

char *get_controls(char *line, int *i)
{
	int k;
	char *res;
	char q[2];

	k = *i;
	if (line[k] == '>' && line[k + 1] == '>')
	{
		if (!(res = (char *)malloc(sizeof(char) * 3)))
			return (NULL);
		else
		{	*i = k + 2;
			res = ft_strdup(">>\0");
		}
	}
	else
	{
		q[0] = line[k];
		if (!(res = (char *)malloc(sizeof(char) * 2)))
			return (NULL);
		else
		{
			*i = k + 1;
			res = ft_strdup(q);
		}
	}
	return (res);
}