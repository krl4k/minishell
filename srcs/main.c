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

	free(pwd);
	prompt = "٩(◕‿◕｡)۶$\0";
	ft_putstr_fd(prompt, 1);
}

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

int main(int ac, char **av, char **env)
{
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
	}
	return (EXIT_SUCCESS);
}
