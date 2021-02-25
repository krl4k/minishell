/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 17:39:05 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/25 11:25:08 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **cmd, t_all *all)
{
	char	*pwd;
	int		i;

	i = 0;
	(void)cmd;
	if (!(pwd = getcwd(NULL, 0)))
	{
		while (all->env_array->str[i])
		{
			if (ft_strcmp("PWD", all->env_array->key[i]) == 0)
				if (all->env_array->value[i])
				{
					ft_putendl_fd(all->env_array->value[i], 1);
					break ;
				}
			i++;
		}
		if (i == all->env_array->current_size)
			ft_perror("pwd");
	}
	else
		ft_putendl_fd(pwd, 1);
	if (pwd)
		free(pwd);
}
