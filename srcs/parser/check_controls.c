/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/13 20:37:59 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_controls(t_all *all)
{
	int	i;

	i = 0;
	while (all->command_argv[i])
	{
        if ((!ft_strcmp("<", all->command_argv[i]) || !ft_strcmp(">", all->command_argv[i]) ||
            !ft_strcmp("|", all->command_argv[i]) || !ft_strcmp(">>", all->command_argv[i])) && all->flag[i] &&
            (!all->command_argv[i + 1] || ((!ft_strcmp("<", all->command_argv[i + 1]) ||
            !ft_strcmp(">", all->command_argv[i + 1]) || !ft_strcmp("|", all->command_argv[i + 1]) ||
            !ft_strcmp(">>", all->command_argv[i + 1])) && all->flag[i + 1])))
        {
            syntax_error(all->command_argv[i]);
            return (1);
        }
		i++;
	}
	return (0);
}
