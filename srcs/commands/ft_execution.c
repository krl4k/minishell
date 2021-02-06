/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:35 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:44:36 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_pipes(t_all *all)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (all->command_argv[i])
	{
		if ((len = ft_strlen(all->command_argv[i])) > 0)
			if (ft_strcmp(all->command_argv[i], "|") == 0
				||ft_strcmp(all->command_argv[i], ">") == 0
				||ft_strcmp(all->command_argv[i], "<") == 0
				||ft_strcmp(all->command_argv[i], ">>") == 0)
			{
				pipes_work(all);
				return (1);
			}
		i++;
	}
	return (0);
}

void ft_execution(t_all *all)
{

//	printf("commands = \n");
//	int i = 0;
//
//	for (int j = 0; all->command_argv[j]; ++j)
//	{
//		printf("command[%d] = %s\n", j, all->command_argv[j]);
//	}
	if (is_pipes(all))
		return;
//	while (all->command_argv[i])
//	{
//		int len = 0;
//		if ((len = ft_strlen(all->command_argv[i])) > 0)
//			if (ft_strcmp(all->command_argv[i], "|") == 0
//				||ft_strcmp(all->command_argv[i], ">") == 0
//				||ft_strcmp(all->command_argv[i], "<") == 0
//				||ft_strcmp(all->command_argv[i], ">>") == 0)
//			{
//				pipes_work(all);
//				return;
//			}
//		i++;
//	}
//	for (int j = 0; all->command_argv[j]; ++j)
//	{
//		printf("exec cmd[%d] = %s\n", j, all->command_argv[j]);
//	}
	if (!all->command_argv[0])
		return;
	if (!ft_strcmp(all->command_argv[0], "echo"))
		ft_echo(all->command_argv);
	else if (!ft_strcmp(all->command_argv[0], "pwd"))
		ft_pwd(all->command_argv);
	else if (!ft_strcmp(all->command_argv[0], "exit"))
		ft_exit(all->command_argv);
	else if (!ft_strcmp(all->command_argv[0], "cd"))
		ft_cd(all);
	else if (!ft_strcmp(all->command_argv[0], "env"))
		ft_env(all);
	else if (!ft_strcmp(all->command_argv[0], "unset"))
		ft_unset(all);
	else if (!ft_strcmp(all->command_argv[0], "export"))
		ft_export(all);
	else
		execute(all);
	//printf("end commands\n");
}
