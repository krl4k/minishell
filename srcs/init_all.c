/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 13:42:07 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_all(t_all *all)
{
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
    all->pwd = 0;
    all->cd = 0;
    all->echo = 0;
    all->export = 0;
    all->unset = 0;
    all->env = 0;
    all->exit = 0;
    all->bin_command = 0;
	all->command_argv = NULL;

}
