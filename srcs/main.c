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

/*void get_commands(char *line)
{
    char pwd[1024];

    if (!ft_strncmp("exit", line, 4)) {
        write(1, "exit\n", 5);
        exit(0);
    }
    if (!ft_strncmp("pwd", line, 3))
    {
        getcwd(pwd, 1024);
        ft_putendl_fd(pwd, 1);
    }
}*/

void    ft_pwd(char **cmd)
{
   char pwd[1024];

   getcwd(pwd, 1024);
   ft_putendl_fd(pwd, 1);
}

void    ft_exit(char **cmd)
{
    int ret;

    ret = 0;
    if (cmd[1])
        ret = ft_atoi(cmd[1]);
    ft_free_split(cmd);
    exit(ret);
}

void    ft_execution(char **cmd)
{
    if (!ft_strncmp(cmd[0], "pwd", 3))
        ft_pwd(cmd);
    if (!ft_strncmp(cmd[0], "exit", 4))
        ft_exit(cmd);
}

void    get_command(char *full_cmd)
{
    char **cmd;

    cmd = ft_setsplit(full_cmd, " ");
    ft_execution(cmd);

}

void    get_commands(char *line)
{
    char **cmds;

    cmds = ft_setsplit(line, ";");
    int i = 0;
    while (cmds[i])
    {
        get_command(cmds[i]);
        free(cmds[i]);
        i++;
    }
}

/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/
void get_input(void)
{
	char *line;

	get_next_line(0, &line);
	get_commands(line);
	free(line);
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

/*!
** Entrypoint in minishell
** 
** @param	ac	arguments count
** @param	av	arguments
** @param	env	environment variables
** @return	0 if success
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
		get_input();
		//! todo : get the line, start parsing and sending for execution
		//may be execute return status and break a proccess
		all->bin_command = 1;
		// av not main argv
		//if (execute(all, line, av, env) == 0)
		//	break;

	}
	return (EXIT_SUCCESS);
}