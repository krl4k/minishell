/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:39:09 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_quotes(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			i++;
		str++;
	}
	return (i);
}

int check_flag(char *cmd)
{
	int i;

	i = 0;
	if (cmd[i] != '-')
		return (0);
	i++;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void    ft_echo(char **cmd)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (cmd[i])
		flag = check_flag(cmd[1]);
	while(cmd[i])
	{
		if (check_flag(cmd[i]) && flag)
		{
			i++;
			continue;
		}
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
}
