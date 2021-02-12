/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:50:02 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 17:50:03 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->env_array->current_size)
	{
		if (ft_strchr(all->env_array->str[i], '='))
			ft_putendl_fd(all->env_array->str[i], 1);
		i++;
	}
	return (0);
}
