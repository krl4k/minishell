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

int key_len(char *line, t_all *all)
{
	int i;

	i = 0;
	while (line[all->i + i] && !ft_strchr("\'\" <>|;", line[all->i + i]))
		i++;
	return (i);
}
static char *get_key(char *line, t_all *all)
{
	char	*key;
	int		k;

	all->i++;
	if (!(key = (char *)malloc(sizeof(char) * (key_len(line, all) + 1))))
		return (NULL);
	k = 0;
	while (line[all->i] && !ft_strchr("\'\" <>|;$", line[all->i]))
		key[k++] = line[all->i++];
	key[k] = '\0';
	return (key);
}

char *get_env(char *line, t_all *all)
{
	char	*key;
	char	*env;

	if (!(key = get_key(line, all)))
		return (NULL);
	env = get_env_by_key(all, key);
	free(key);
	return(env);

}
char *substitution_env(t_all *all)
{
	char	*new;
	char 	*env;

	if (!(new = (char *)ft_calloc(sizeof(char), 2)))
		return (NULL);
	all->i = 0;
	while (all->input[all->i])
	{
		if (all->input[all->i])
			if (all->input[all->i] == '$' && all->input[all->i - 1] != '\\' &&
				all->input[all->i + 1])
			{
				env = get_env(all->input, all);
				new = ft_strjoin_free(new, env);
				continue;
			}
		new = ft_strjoinchar(new, all->input[all->i]);
		all->i++;
	}
	free(all->input);
	return (new);
}