/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/14 17:57:14 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes3(char *line, t_all *all)
{
	char *tmp;
	char *tmp2;

	if (line[all->i] && ft_strchr("\'\"", line[all->i]) &&
		!ft_strchr("<>|", line[all->i - 1]) &&
		!IS_SPACE(line[all->i - 1]))
	{
		tmp = all->command_argv[all->k];
		if (!(tmp2 = get_in_quotes(line, all)))
			return (0);
		if (!(all->command_argv[all->k] = ft_strjoin(all->command_argv[all->k],
				tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	return (1);
}

static int	check_quotes2(char *line, t_all *all)
{
	char *tmp;
	char *tmp2;

	if (ft_strchr("\'\"", line[all->i - 1]) && !ft_strchr("\'\"<>|",
			line[all->i]) && !IS_SPACE(line[all->i]))
	{
		tmp = all->command_argv[all->k];
		if (!(tmp2 = get_word(line, all)))
			return (0);
		if (!(all->command_argv[all->k] = ft_strjoin(all->command_argv[all->k],
			tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	else if (!(check_quotes3(line, all)))
		return (0);
	return (1);
}

static int	check_quotes(char *line, t_all *all)
{
	if (ft_strchr("\'\"", line[all->i]))
	{
		if (!(all->command_argv[all->k] = get_in_quotes(line, all)))
			return (0);
	}
	else if (!ft_strchr("\'\"<>|", line[all->i]) && !IS_SPACE(line[all->i]))
	{
		if (!(all->command_argv[all->k] = get_word(line, all)))
			return (0);
	}
	else if (ft_strchr("<>|", line[all->i]))
	{
		if (!(all->command_argv[all->k] = get_controls(line, all)))
			return (0);
	}
	if (!check_quotes2(line, all))
		return (0);
	all->k++;
	return (1);
}

int			parse_line(char *line, t_all *all)
{
	all->k = 0;
	while (line[all->i])
	{
		while (IS_SPACE(line[all->i]) && line[all->i])
			all->i++;
		if (line[all->i])
		{
			if (!check_quotes(line, all))
				continue;
			else
			{
				if (!(all->command_argv = ft_realloc_args(all->command_argv,
					all->k + 1)))
					return (0);
			}
		}
	}
	return (1);
}
