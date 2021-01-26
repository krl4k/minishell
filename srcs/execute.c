/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:51:13 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 11:51:15 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
** return built in function
**
*/
static	int	is_builtin(t_all *all, char *command)
{
	int i;

	i = 0;
	while (all->impl_builtin[i])
	{
		if (ft_strncmp(command, all->impl_builtin[i], ft_strlen(command)) == 0)
			return i;
		i++;
	}
	return (-1);
}

void		my_builtin(char *command)
{

}



int			execute(t_all *all, char *command, char **argv, char **env)
{
	int status;
	int num_command;

	num_command = 0;
	pid_t pid = fork();
	if (pid < 0)
		perror("fork()\n");
	if (pid == 0)
	{
		if ((num_command = is_builtin(all, command)) != -1)
			my_builtin(all->impl_builtin[num_command]);
//		printf("CHILD:\n");
		status = execve(command,argv,env);
		exit(status);
	}
	else
	{
		wait(&status);
		printf("Выполнено успешно!\n");
	}

	return (EXIT_SUCCESS);
}