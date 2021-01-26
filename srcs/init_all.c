/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 11:39:32 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void builtin_init(t_all *all)
{
	if (!(all->impl_builtin = (char **)malloc(8 * sizeof(char *))))
		perror(MALLOC_ERROR);
	all->impl_builtin[0] = "echo";
	all->impl_builtin[1] = "cd";
	all->impl_builtin[2] = "pwd";
	all->impl_builtin[3] = "export";
	all->impl_builtin[4] = "unset";
	all->impl_builtin[5] = "env";
	all->impl_builtin[6] = "exit";
	all->impl_builtin[7] = NULL;
}

void init_all(t_all *all)
{
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
	builtin_init(all);
}
