/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:28:14 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/28 10:28:16 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
** \author fgrisell
** removes an element from the environment variable by key
*/
int ft_unset(t_all *all)
{
	int i;
	int j;

	i = 1;
	while (all->command_argv[i])
	{
		printf("cmd = %s\n", all->command_argv[i]);
		j = 0;
		while (all->env_array->str[j])
		{
			if (ft_strncmp(all->env_array->str[j], all->command_argv[i], ft_strlen(all->command_argv[i])) == 0)
			{
				all->env_array->delete_one_by_key(&all->env_array, all->command_argv[i]);
			}
			j++;
		}
		i++;
	}
	return (0);
}
