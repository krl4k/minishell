/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 12:34:18 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char *prompt;

<<<<<<< HEAD
	free(pwd);
=======
>>>>>>> b4f71bee3ceb0af4d46408fc34703ae6a1c2e2b0
	prompt = "٩(◕‿◕｡)۶$\0";
	ft_putstr_fd(prompt, 1);
}

<<<<<<< HEAD
void commands(char *line)
{
	char *pwd;
	
	if (!ft_strncmp("^C", line, 2))
		return ;
	if (!ft_strncmp("pwd", line, 3))
	{
		pwd = getcwd(pwd, 0);
	//	write(1, pwd, ft_strlen(pwd));
		free(pwd);
	//	write(1, "\n", 1);
	}	
	if (!ft_strncmp("exit", line, 4))
	{	
		write(1, "exit\n", 5);
		exit(0);
	}

=======

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
>>>>>>> b4f71bee3ceb0af4d46408fc34703ae6a1c2e2b0
}

void	no_interrupt(int signal_no)
{
<<<<<<< HEAD
	if (signal_no == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt();
		signal(SIGINT, no_interrupt);
	}
=======
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
>>>>>>> b4f71bee3ceb0af4d46408fc34703ae6a1c2e2b0
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
<<<<<<< HEAD
	pid_t pid;
	char *input;

	pid = getpid();
	signal(SIGINT, no_interrupt);
	while (1)
	{
		print_prompt();
		get_next_line(0, &input);
		commands(input);
		free(input);
=======
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

>>>>>>> b4f71bee3ceb0af4d46408fc34703ae6a1c2e2b0
	}
	return (EXIT_SUCCESS);
}