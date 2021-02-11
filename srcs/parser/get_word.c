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

static int ft_strlen_set(char *str, const char *set, t_all *all)
{
	(void)set;
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (ft_strchr("\'\" <>|;", str[k]) && str[i - 1] != '\\')
			return (k);
		if (str[i] == '\\' && ft_strchr("\'\"\\$<>;|", str[i + 1]))
			i++;
		if (str[i] == '$' && str[i - 1] != '\\')
		{
			j = all->i;
			k += ft_strlen(get_env(str, all));
			all->i = j;
		}
		k++;
		i++;
	}
	return (i);
}

char *get_word(char *line, t_all *all)
{
	char	*res;
	int		size;
	int		k;
	char	*env;

	k = 0;
	if (!(size = ft_strlen_set(&line[all->i], "\'\" <>|;", all)))
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (k < size)
	{
		if (ft_strchr("\'\" <>|;", line[all->i]) && line[all->i - 1] !='\\')
			break;
		if (line[all->i] == '$' && line[all->i - 1] != '\\')
		{
			env = get_env(line, all);
			if (!*env)
				return (NULL);
			while (*env)
				res[k++] = *env++;
			continue;
		}
		if (line[all->i] == '\\' && ft_strchr("\'\"\\$<>|;", line[all->i + 1]))
			all->i++;
		res[k++] = line[all->i++];
	}
	res[k] = '\0';
	return (res);
}

