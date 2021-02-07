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
		all->i += 2;
		if (!(res = ft_strdup(">>\0")))
			return (NULL);
	}
	else
	{
		q[0] = line[all->i];
		all->i++;
		if  (!(res = ft_strdup(q)))
			return (NULL);
	}
	return (res);
}