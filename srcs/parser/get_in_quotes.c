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

void *syntax_error(void)
{
	write(1, "Syntax error\n", 13);
	return (NULL);
}

char	*get_in_quotes(char *line, t_all *all)
{
	char	*res;
	char	q;
	char	*env;

	q = line[all->i];
	all->i++;
	if (!(res = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	while (line[all->i])
	{
		if (line[all->i] == q && line[all->i - 1] !='\\')
			break;
		if (line[all->i] == '$' && line[all->i - 1] != '\\')
		{
			env = get_env(line, all);
			res = ft_strjoin_free(res, env);
			continue;
		}
		if (line[all->i] == '\\' && ft_strchr("\'\"\\$<>|;", line[all->i + 1]))
			all->i++;
		res = ft_strjoinchar(res, line[all->i]);
		all->i++;
	}
	if (line[all->i] != q)
		return (syntax_error());
	all->i++;
	return (res);
}
