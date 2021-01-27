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
    char c_pwd[1024];

    if (!ft_strncmp("exit", line, 4)) {
        write(1, "exit\n", 5);
        exit(0);
    }
    if (!ft_strncmp("c_pwd", line, 3))
    {
        getcwd(c_pwd, 1024);
        ft_putendl_fd(c_pwd, 1);
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

/*!
** set all->command_argv (command_argv this is a null-terminated array of strings)
** \authors fgrisell and mwinter
** \version Temporary
** \example FIRST ARGUMENT: BIN FILE or BUILTIN COMMAND - argv[0] = /bin/ls
** \example FLAGS	(n > 0 && n < argc) - argv[n] = "-la" (flag)(optional)
** \example LAST ARGUMENT: argv[argc] = NULL;
** \warning The last argument should always be NULL!
** \todo processing commands and putting them in an array
*/

void    ft_execution(t_all *all, char **cmd)
{
//	printf("all cmd[0] = %s\n", cmd[0]);
//	printf("all cmd[1] = %s\n", cmd[1]);
	int i = 0;
	all->command_argv = (char **) malloc(3 * sizeof(char *));
	if (cmd[i])
	{
		all->command_argv[i] = ft_strdup(cmd[i]); //bin file or command
		i++;
	}
	if (cmd[i])
	{
		all->command_argv[i] = ft_strdup(cmd[i]); //flags, pars a lot command
		i++;
	}
//	else
	all->command_argv[i] = NULL; //last argument always NULL
	all->c_bin_command = 1;//set flag
//    if (!ft_strncmp(cmd[0], "c_pwd", 3))
//        ft_pwd(cmd);
    if (!ft_strncmp(cmd[0], "exit", 4))
        ft_exit(cmd);
}

void    get_command(t_all *all, char *full_cmd)
{
    char **cmd;

    cmd = ft_setsplit(full_cmd, " ");
    ft_execution(all, cmd);
}

void    get_commands(t_all *all, char *line)
{
    char **cmds;

    cmds = ft_setsplit(line, ";");
    int i = 0;
    while (cmds[i])
    {
        get_command(all, cmds[i]);
        free(cmds[i]);
        i++;
    }
}

/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/
void get_input(t_all *all)
{
	char *line;

	get_next_line(0, &line);
	get_commands(all, line);
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
	char *line;

	init_all(&all);
	while (1)
	{
		print_prompt();
		//make_fork(ac, av, env, pid);
		//while(1) ?? for a large number of teams
		signal(SIGINT, no_interrupt);
		get_input(all);
		//! todo : get the line, start parsing and sending for execution
		//may be execute return status and break a proccess
		// av not main argv
		execute(all, line, av, env);
	}
	return (EXIT_SUCCESS);
}