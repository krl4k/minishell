
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

static int check_quotes(char *line, int i, char **cmd, int *k)
{
	int j;
	char *tmp;
	char *tmp2;

	j = *k;
	if (ft_strchr("\'\"", line[i]))
	{
		if (!(*cmd = get_in_quotes(line, &i)))
			return (0);
	}
	else if (!ft_strchr("\'\"<>|; ", line[i]))
	{
		if (!(*cmd = get_word(line, &i)))
			return (0);
	}
	else if (ft_strchr("<>|;", line[i]))
	{
		if (!(*cmd = get_controls(line, &i)))
			return (0);
	}
	if (ft_strchr("\'\"", line[i - 1]) && !ft_strchr("\'\"<>|;", line[i]) && !IS_SPACE(line[i]))
	{
		tmp = *cmd;
		tmp2 = get_word(line, &i);
		if (!(*cmd = ft_strjoin(*cmd, tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	else if (ft_strchr("\'\"", line[i]) && !ft_strchr("\'\"<>|;", line[i - 1]) && !IS_SPACE(line[i - 1]))
	{
		tmp = *cmd;
		tmp2 = get_in_quotes(line, &i);
		if (!(*cmd = ft_strjoin(*cmd, tmp2)))
			return (0);
		free(tmp2);
		free(tmp);
	}
	j++;
	*k = j;
	return (i);
}

char	**parse_line(char *line, char **cmd)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (line[i])
	{
		while (IS_SPACE(line[i]) && line[i])
			i++;
		if (!(i = check_quotes(line, i, &cmd[k], &k)))
		{
			ft_free_split(cmd);
			return (NULL);
		}
		else
		{
			if (!(cmd = ft_realloc_args(cmd,k + 1)))
			{
				ft_free_split(cmd);
				return (NULL);
			}
			continue;
		}
	}
	return (cmd);
}