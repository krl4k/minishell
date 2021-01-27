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

void	print_prompt(int fd)
{
	char *prompt;

	prompt = "٩(◕‿◕｡)۶$\0";
	ft_putstr_fd(prompt, fd);
}

void    ft_pwd(char **cmd)
{
   char pwd[1024];

   getcwd(pwd, 1024);
   ft_putendl_fd(pwd, 1);
}

int     is_numeric(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
        if (!ft_isdigit(cmd[i++]))
            return (0);
    return (1);
}

void    ft_exit(char **cmd)
{
    int ret;

    ret = 0;
    if (cmd[1] && is_numeric(cmd[1]))
        ret = ft_atoi(cmd[1]);
    else if (cmd[1] && !is_numeric(cmd[1]))
    {
        write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
        write(2, ": ", 2);
        write(2, cmd[0], ft_strlen(cmd[0]));
        write(2, ": ", 2);
        ft_putendl_fd("numeric argument required!", 2);
    }
    ft_free_split(cmd);
    exit(ret);
}

int     check_n(char *flag)
{
    int i;

    i = 1;
     while (flag[i])
    {
        if (flag[i] != 'n')
            return (1);
        i++;
    }
    return (0);
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

void    ft_execution(t_all *all)
{

    if (!ft_strncmp(all->command_argv[0], "pwd", 3))
        ft_pwd(all->command_argv);
    else if (!ft_strncmp(all->command_argv[0], "exit", 4))
        ft_exit(all->command_argv);
    else if (!ft_strncmp(all->command_argv[0], "cd", 2))
        ft_cd(all);
    /*else if (!ft_strncmp(all->command_argv[0], "env", 3))
        ft_env(all);
    else if (!ft_strncmp(all->command_argv[0], "unset", 5))
        ft_unset(all);
    else if (!ft_strncmp(all->command_argv[0], "export", 6))
        ft_export(all);*/
    else
    {
        all->c_bin_command = 1;//set flag
        execute(all);
    }
}

void    get_command(t_all *all, char *full_cmd)
{
    all->command_argv = ft_command(full_cmd);
    ft_execution(all);
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
		print_prompt(1);
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

	init_all(&all);
	all->av = av;
	all->env = env;
	while (1)
	{
		print_prompt(1);
		//make_fork(ac, av, env, pid);
		//while(1) ?? for a large number of teams
		signal(SIGINT, no_interrupt);
		get_input(all);
	}
	return (EXIT_SUCCESS);
}