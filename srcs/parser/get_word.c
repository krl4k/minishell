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

char *get_word(char *line, t_all *all)
{
	char	*res;
	char	*env;

	if (!(res = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	while (line[all->i])
	{
		if (ft_strchr("\'\" <>|;", line[all->i]) && line[all->i - 1] !='\\')
			break;
		if (line[all->i] == '$' && line[all->i - 1] != '\\')
		{
//			char *temp;
			env = get_env(line, all);
//			temp = ft_substr(line, 0, all->i);

//			char *new_line;

//			printf("env = %s\n", env);
//			if (!*env)

			res = ft_strjoin_free(res, env);
			continue;
		}
		if (line[all->i] == '\\' && ft_strchr("\'\"\\ $<>|;", line[all->i + 1]))
			all->i++;
		res = ft_strjoinchar(res, line[all->i]);
		all->i++;
	}
	return (res);
}

