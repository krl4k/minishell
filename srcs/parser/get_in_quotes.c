/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/14 17:53:42 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*syntax_error(char *error)
{
	g_exit_code = 258;
	if (!error)
		write(2, "Syntax error\n", 13);
	else
	{
		write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
		write(2, "syntax error near unexpected token \0",
			ft_strlen("syntax error near unexpected token \0"));
		write(2, "`", 1);
		write(2, error, ft_strlen(error));
		ft_putendl_fd("\'", 2);
	}
	return (NULL);
}

char	*get_in_quotes(char *line, t_all *all)
{
	char *res;
	char q;

	q = line[all->i];
	all->i++;
	if (!(res = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	while (line[all->i])
	{
		if ((line[all->i] == q && line[all->i - 1] != '\\') || (line[all->i - 2] == '\\'
				&& line[all->i - 1] == '\\' && line[all->i] == q))
			break ;
		if (line[all->i] == '\\' && ft_strchr("\'\"\\<>|;", line[all->i + 1]))
			all->i++;
		res = ft_strjoinchar(res, line[all->i]);
		all->i++;
	}
	if (line[all->i] != q)
	{
		free(res);
		return (syntax_error(NULL));
	}
	all->i++;
	return (res);
}
