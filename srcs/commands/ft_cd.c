/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:00:41 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 15:00:42 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_all *all)
{
	if ((chdir(all->command_argv[1])) == -1)
	{
		ft_putstr_fd(PROMT_ERROR, 2);
		ft_putstr_fd(all->command_argv[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(all->command_argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (0);
}