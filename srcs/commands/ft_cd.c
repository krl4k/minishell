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
	char *command;
	char *temp;
	char *error;

//	command = ft_strjoin(all->command_argv[0], ": ");
//	error = ft_strjoin(PROMT_ERROR, command);

//	free(command);
	if ((chdir(all->command_argv[1])) == -1)
	{
		command = ft_strjoin(all->command_argv[0], ": ");
		error = ft_strjoin(PROMT_ERROR, command);
		free(command);
//		temp = ft_strjoin(PROMT, command);
//		free(command);
		command = ft_strjoin(error, strerror(errno));
		ft_putendl_fd(command, 2);
		free(error);
		free(command);
	}
//	free(error);
//	free(command);
	return (0);
}