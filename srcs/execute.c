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


int execute(t_all *all, char *line, char **argv, char **env)
{
//	printf("execute---------------------\n");
	if (all->c_bin_command)
	{
//		printf("BIN_EXEC\n");
		bin_func(all, argv);
	}
	return (EXIT_SUCCESS);
}