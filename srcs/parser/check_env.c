/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/19 15:03:39 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_env(t_all *all, char **new)
{
	char *env;

	if (all->input[all->i])
	{
		if (all->input[all->i] == '$' &&
			all->input[all->i - 1] != '\\' && all->input[all->i - 1] != '\'' &&
			all->input[all->i + 1] != '\0')
		{
			if (ft_isdigit(all->input[all->i + 1]))
			{
				all->i += 2;
				return (0);
			}
			env = get_env(all->input, all);
			*new = ft_strjoin_free(*new, env);
			return (1);
		}
	}
	return (0);
}

void	substitution_env3(t_all *all, char **new)
{
	if (ft_strchr("\'\"", all->input[all->i]) && all->input[all->i] != '\\')
	{
		*new = ft_strjoinchar(*new, all->input[all->i]);
		all->q = all->input[all->i++];
		while (all->input[all->i])
		{
			if (all->input[all->i] == all->q && all->input[all->i] != '\\')
			{
				*new = ft_strjoinchar(*new, all->input[all->i]);
				all->i++;
				break ;
			}
			if (all->input[all->i] == '$' && all->q != '\'' &&
				all->input[all->i - 1] != '\\')
				if (check_env(all, new))
					continue ;
			*new = ft_strjoinchar(*new, all->input[all->i]);
			all->i++;
		}
	}
}
