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

char *get_controls(char *line, t_all *all)
{

	char *res;
	char q[2];

	if (line[all->i] == '>' && line[all->i + 1] == '>')
	{
		if (!(res = (char *)malloc(sizeof(char) * 3)))
			return (NULL);
		else
		{	all->i += 2;
			res = ft_strdup(">>\0");
		}
	}
	else
	{
		q[0] = line[all->i];
		if (!(res = (char *)malloc(sizeof(char) * 2)))
			return (NULL);
		else
		{
			all->i++;
			res = ft_strdup(q);
		}
	}
	return (res);
}