/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:59:44 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/12 20:59:45 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_numeric_neg(char *cmd)
{
	int i;

	i = 0;
	if (cmd[0] == '-' || cmd[0] == '+')
		i++;
	while (cmd[i])
		if (!ft_isdigit(cmd[i++]))
			return (0);
	return (1);
}

static void	wrong_numeric(char **cmd, int ret)
{
	write(1, "exit\n", 5);
	write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
	write(2, ": ", 2);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": ", 2);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, ": ", 2);
	ft_putendl_fd("numeric argument required", 2);
	ret = 255;
	exit(ret);
}

void		ft_exit(char **cmd)
{
	int ret;

	ret = 0;
	if (size_arr(cmd) > 2 && is_numeric_neg(cmd[1]))
	{
		if (is_numeric(cmd[1]))
			write(1, "exit\n", 5);
		write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": ", 2);
		ft_putendl_fd("too many arguments", 2);
		g_exit_code = 1;
		return ;
	}
	if (cmd[1] && is_numeric_neg(cmd[1]))
		ret = ft_atoi(cmd[1]);
	else if (cmd[1] && !is_numeric_neg(cmd[1]))
		wrong_numeric(cmd, ret);
	write(1, "exit\n", 5);
	if (ret < 0)
		exit(ret);
	ret = ret > 255 ? 255 : ret;
	ft_free_split(cmd);
	exit(ret);
}
