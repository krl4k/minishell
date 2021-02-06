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

void ft_execution(t_all *all)
{

	printf("commands = \n");
	int i = 0;

	for (int j = 0; all->command_argv[j]; ++j)
	{
		printf("command[%d] = %s\n", j, all->command_argv[j]);
	}
	while (all->command_argv[i])
	{
//		printf("%s\n", all->command_argv[i]);
		int len = 0;
		if ((len = ft_strlen(all->command_argv[i])) > 0)
			if (ft_strcmp(all->command_argv[i], "|") == 0
				||ft_strcmp(all->command_argv[i], ">") == 0
				||ft_strcmp(all->command_argv[i], "<") == 0
				||ft_strcmp(all->command_argv[i], ">>") == 0)
			{
				pipes_work(all);
				return;
			}
		i++;
	}

//	for (int j = 0; all->command_argv[j]; ++j)
//	{
//		printf("exec cmd[%d] = %s\n", j, all->command_argv[j]);
//	}
	if (!all->command_argv[0])
		return;
	if (!ft_strncmp(all->command_argv[0], "echo", 4))
		ft_echo(all->command_argv);
	else if (!ft_strncmp(all->command_argv[0], "pwd", ft_strlen(all->command_argv[0])))
		ft_pwd(all->command_argv);
	else if (!ft_strncmp(all->command_argv[0], "exit", ft_strlen(all->command_argv[0])))
		ft_exit(all->command_argv);
	else if (!ft_strncmp(all->command_argv[0], "cd", ft_strlen(all->command_argv[0])))
		ft_cd(all);
	else if (!ft_strncmp(all->command_argv[0], "env", ft_strlen(all->command_argv[0])))
		ft_env(all);
	else if (!ft_strncmp(all->command_argv[0], "unset", ft_strlen(all->command_argv[0])))
		ft_unset(all);
	else if (!ft_strncmp(all->command_argv[0], "export", ft_strlen(all->command_argv[0])))
		ft_export(all);
	else
	{

		execute(all);
	}
	printf("after execution\n");
//	ft_free_split(all->command_argv);
}