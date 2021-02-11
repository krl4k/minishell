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

static int check_queotes2(char *line, t_all *all)
{
	char *tmp;
	char *tmp2;

	if (ft_strchr("\'\"", line[all->i - 1]) && !ft_strchr("\'\"<>|;",
						   line[all->i]) && !IS_SPACE(line[all->i]))
	{
		tmp = all->tmp[all->k];
		tmp2 = get_word(line, all);
		if (!(all->tmp[all->k] = ft_strjoin(all->tmp[all->k], tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	else if (line[all->i] && ft_strchr("\'\"", line[all->i]) &&
		!ft_strchr("<>|;", line[all->i - 1]) &&
			!IS_SPACE(line[all->i - 1]))
	{
		tmp = all->tmp[all->k];
		tmp2 = get_in_quotes(line, all);
		if (!(all->tmp[all->k] = ft_strjoin(all->tmp[all->k], tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	return (1);
}

static int check_quotes(char *line, t_all *all)
{

	if (ft_strchr("\'\"", line[all->i]))
	{
		if (!(all->tmp[all->k] = get_in_quotes(line, all)))
			return (0);
	}
	else if (!ft_strchr("\'\"<>|;", line[all->i]) && !IS_SPACE(line[all->i]))
	{
		if (!(all->tmp[all->k] = get_word(line, all)))
			return (0);
	}
	else if (ft_strchr("<>|;", line[all->i]))
	{
		if (!(all->tmp[all->k] = get_controls(line, all)))
			return (0);
	}
	if (!check_queotes2(line, all))
		return (0);
	all->k++;
	return (1);
}

int 		parse_line(char *line, t_all *all)
{
	all->i = 0;
	all->k = 0;
	while (line[all->i])
	{
		while (IS_SPACE(line[all->i]) && line[all->i])
			all->i++;
		if (line[all->i])
		{
			if (!check_quotes(line, all))
				return (0);
			else
			{
				if (!(all->tmp = ft_realloc_args(all->tmp, all->k + 1)))
					return (0);
				continue;
			}
		}
	}
	return (1);
}