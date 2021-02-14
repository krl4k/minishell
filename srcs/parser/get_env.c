/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/14 18:09:39 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			key_len(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[all->i + i] && !ft_strchr("\'\" <>|;", line[all->i + i]))
		i++;
	return (i);
}

static char	*get_key(char *line, t_all *all)
{
	char	*key;
	int		k;

	all->i++;
	if (!(key = (char *)malloc(sizeof(char) * (key_len(line, all) + 1))))
		return (NULL);
	k = 0;
	while (line[all->i] && !ft_strchr("\'\" <>|;$\\", line[all->i]))
		key[k++] = line[all->i++];
	key[k] = '\0';
	return (key);
}

char		*get_env(char *line, t_all *all)
{
	char	*key;
	char	*env;

	if (!(key = get_key(line, all)))
		return (NULL);
	env = get_env_by_key(all, key);
	free(key);
	return (env);
}

static int	substitution_env2(t_all *all, char **new)
{
	char	q;
	int		i;

	if (ft_strchr("\'\"", all->input[all->i]) && all->input[all->i] != '\\')
	{
		q = all->input[all->i];
		while (all->input[all->i] != q && all->input[all->i])
		{
			*new = ft_strjoinchar(*new, all->input[all->i]);
			all->i++;
		}
	}
	if (all->input[all->i] == ';' && all->input[all->i - 1] != '\\')
	{
		i = all->i;
		get_commands(all, *new);
		if (!(*new = (char *)ft_calloc(sizeof(char), 2)))
			return (0);
		all->i = ++i;
		return (1);
	}
	return (0);
}

void		substitution_env(t_all *all)
{
	char	*new;

	all->i = 0;
	if (!(new = (char *)ft_calloc(sizeof(char), 2)))
		return ;
	while (all->input[all->i])
	{
		if (check_env(all, &new))
			continue ;
		if (substitution_env2(all, &new))
				continue ;
		new = ft_strjoinchar(new, all->input[all->i]);
		all->i++;
	}
	if (new)
		get_commands(all, new);
	free(all->input);
}
