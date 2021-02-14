/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/14 17:52:58 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char *line, t_all *all)
{
	char *res;

	if (!(res = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	while (line[all->i])
	{
		if (ft_strchr("\'\" <>|", line[all->i]) && line[all->i - 1] != '\\')
			break ;
		if (line[all->i] == '\\' && ft_strchr("\'\"\\ <>|$", line[all->i + 1]))
			all->i++;
		else if ((line[all->i] == '\\' && !ft_strchr("\'\"\\ <>|$", line[all->i + 1])))
			all->i++;
		res = ft_strjoinchar(res, line[all->i]);
		all->i++;
	}
	return (res);
}
