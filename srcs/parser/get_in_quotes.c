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

static int ft_strlen_c(char *str, char q, t_all *all)
{
	int k;
	int i;
	int j;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == q && str[i - 1] != '\\')
			return (k);
		if (str[i] == '\\' && ft_strchr("\'\"$<>;|", str[i + 1]))
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
	if (str[i] != q)
		return (0);
	else
		k++;
	return (k);
}

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
	int		size;
	int		k;

	q = line[all->i];
	all->i++;
	k = 0;
	if (!(size = ft_strlen_c(&line[all->i], q, all)))
		return (syntax_error());
	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (line[all->i])
	{
		if (line[all->i] == q && line[all->i - 1] !='\\')
			break;
		if (line[all->i] == '$' && line[all->i - 1] != '\\')
		{
			env = get_env(line, all);
			while(*env)
				res[k++] = *env++;
			continue;
		}
		if (line[all->i] == '\\' && ft_strchr("\'\"\\$<>|;", line[all->i + 1]))
			all->i++;
		res[k++] = line[all->i++];
	}
	res[k] = '\0';
	all->i++;
	return (res);
}
