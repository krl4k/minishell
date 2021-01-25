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
	char *pwd;
	char *prompt;

	pwd = getcwd(pwd, 0);
	ft_putstr_fd(pwd, 1);
	free(pwd);
	prompt = "٩(◕‿◕｡)۶$\0";
	ft_putstr_fd(prompt, 1);
}

void get_input(char **av)
{
	char *line;

	get_next_line(0, &line);
	free(line);

}

int	make_fork(int ac, char **av, char **env,pid_t status)
{
	pid_t pid;

	if ((pid = fork() < 0))
		perror("fork < 0");
	if (pid == 0)
		printf("CHILD\n");
	else 
		wait(&status);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av, char **env)
{
	pid_t pid;

	pid = getpid();
	while (1)
	{
		print_prompt();
		//make_fork(ac, av, env, pid);
		get_input(av);

	}
	return (EXIT_SUCCESS);
}
