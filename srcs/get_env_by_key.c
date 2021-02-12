/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_by_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:07:44 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/06 16:07:46 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//\todo echo $a , if a=1  ==> echo $a === 11   why???


char	*get_env_by_key(t_all *all, char *key)
{
	int i;

	i = 0;
	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(g_exit_code));
	while (i < all->env_array->current_size)
	{
		if (ft_strcmp(key, all->env_array->key[i]) == 0)
				return (ft_strdup(all->env_array->value[i]));
		i++;
	}
	return (ft_strdup(""));
}
