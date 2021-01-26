/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/25 19:34:47 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char *prompt;

	prompt = "٩(◕‿◕｡)۶$\0";
	ft_putstr_fd(prompt, 1);
}


/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/
char *get_input(char **av)
{
	char *line;

	get_next_line(0, &line);
	return line;
//	free(line);
}

int	make_fork(int ac, char **av, char **env,pid_t status)
{
	pid_t pid;

	if ((pid = fork() < 0))
		perror("fork < 0");
	if (pid == 0)
	{
		printf("CHILD\n");
		exit(status);
	}
	else
		wait(&status);
	return (EXIT_SUCCESS);
}

/*!
** in while(1) work
**
**
*/

int main(int ac, char **av, char **env)
{
	t_all *all;
//	pid_t pid;
	char *line;
	int status;

	status = 1;
	init_all(all);
//	pid = getpid();
	while (status)
	{
		print_prompt();
		//make_fork(ac, av, env, pid);
		//while(1) ?? for a large number of teams

		line = get_input(av);
		printf("main: line = %s\n", line);
		//! todo : get the line, start parsing and sending for execution
		//may be execute return status and break a procces
		execute(all, line, NULL, env);
		if (status == 0)
			break;

	}
	return (EXIT_SUCCESS);
}