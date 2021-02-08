/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:39:05 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 17:40:40 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(char **cmd)
{
	char *pwd;

	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_perror("pwd");
	}
	else
		ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
}
