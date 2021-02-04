/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:51:13 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 13:41:21 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_all *all)
{
	//	printf("execute---------------------\n");
	//	if (all->c_bin_command)
	//	{
	//		printf("BIN_EXEC\n");
	signal(SIGQUIT, no_interrupt_exec);
	bin_func(all);
	//	}
	return (EXIT_SUCCESS);
}