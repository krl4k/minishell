/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:53:09 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/19 15:12:34 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shifting_argvs(t_all *all, int elem_index)
{
	int		i;
	char	*temp;

	i = 1;
	while (all->command_argv[i])
	{
		if (ft_is_equal(all->command_argv[i], ">")
			|| ft_is_equal(all->command_argv[i], ">"))
			break ;
		i++;
	}
	temp = all->command_argv[elem_index];
	while (elem_index > i)
	{
		all->command_argv[elem_index] = all->command_argv[elem_index - 1];
		elem_index--;
	}
	all->command_argv[elem_index] = temp;
	all->flag[i] = 0;
	all->flag[i + 1] = 1;
}

void	swap_argv(t_all *all)
{
	int i;

	i = 1;
	while (i < all->count_argv)
	{
		if (ft_is_equal(all->command_argv[i], ">"))
			if (all->command_argv[i + 2])
			{
				if (!ft_is_equal(all->command_argv[i + 2], "|")
					&& !ft_is_equal(all->command_argv[i + 2], ">")
					&& !ft_is_equal(all->command_argv[i + 2], "<")
					&& !ft_is_equal(all->command_argv[i + 2], ">>"))
					shifting_argvs(all, i + 2);
				i++;
			}
		i++;
	}
}

int		normal_order(t_all *all, int i)
{
	i = 1;
	while (i < all->count_argv)
	{
		if ((all->flag[i] && ft_is_equal(all->command_argv[i], ">"))
		|| (all->flag[i] && ft_is_equal(all->command_argv[i], ">>")))
		{
			if (i + 2 < all->count_argv)
			{
				if ((!ft_is_equal(all->command_argv[i + 2], "|") &&
					!all->flag[i + 2])
		&& (!ft_is_equal(all->command_argv[i + 2], ">") && !all->flag[i + 2])
		&& (!ft_is_equal(all->command_argv[i + 2], "<") && !all->flag[i + 2])
		&& (!ft_is_equal(all->command_argv[i + 2], ">>") && !all->flag[i + 2]))
				{
					if (!all->command_argv[i + 2])
						return (1);
					return (0);
				}
			}
		}
		i++;
	}
	if (i == all->count_argv - 1)
		return (0);
	return (1);
}
