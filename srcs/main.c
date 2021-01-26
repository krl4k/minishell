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
	//printf("line = %s\n", line);
	return line;
}

void	no_interrupt(int signal_no)
{
	if (signal_no == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt();
		signal(SIGINT, no_interrupt);
	}
}
/*
** Entrypoint in minishell
** 
** @param	ac	arguments count
** @param	av	arguments
** @param	env	environment variables
** @return	0 if success
*/

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

	init_all(&all);
//	pid = getpid();
	while (1)
	{
		print_prompt();
		//make_fork(ac, av, env, pid);
		//while(1) ?? for a large number of teams
		signal(SIGINT, no_interrupt);
		line = get_input(av);
		printf("main: line = %s\n", line);
		//! todo : get the line, start parsing and sending for execution
		//may be execute return status and break a procces

		all->bin_command = 1;
		printf("its work!\n");
		// av not main argv
		if (execute(all, line, av, env) == 0)
			break;

	}
	return (EXIT_SUCCESS);
}