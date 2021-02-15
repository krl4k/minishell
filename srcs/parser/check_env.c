/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/15 14:35:43 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_env(t_all *all, char **new)
{
	char *env;

	if (all->input[all->i])
		if (all->input[all->i] == '$' &&
			!ft_strchr("\\\'", all->input[all->i - 1]) &&
			all->input[all->i + 1] != '\0')
		{
			if (ft_isdigit(all->input[all->i + 1]))
			{
				all->i += 2;
				return (0);
			}
			env = get_env(all->input, all);
			*new = ft_strjoin_free(*new, env);
		}
	return (0);
}
