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

int g_quotes;

void	print_prompt(int fd)
{
	char *prompt;

	prompt = "▓▒░(°◡°)░▒▓\0";
	ft_putstr_fd(prompt, fd);
}

void    ft_pwd(char **cmd)
{
   char *pwd;

   pwd = getcwd(NULL, 0);
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

	if (!ft_strncmp(all->command_argv[0], "echo ", 4))
		ft_echo(all->command_argv[0]);
	if (!ft_strncmp(all->command_argv[0], "pwd", 3))
        ft_pwd(all->command_argv);
    else if (!ft_strncmp(all->command_argv[0], "exit", 4))
        ft_exit(all->command_argv);
    /*else if (!ft_strncmp(all->command_argv[0], "cd", 2))
        ft_cd(all);
    else if (!ft_strncmp(all->command_argv[0], "env", 3))
        ft_env(all);
    else if (!ft_strncmp(all->command_argv[0], "unset", 5))
        ft_unset(all);
    else if (!ft_strncmp(all->command_argv[0], "export", 6))
        ft_export(all);*/
    else
        execute(all);
}

void    get_command(t_all *all, char *cmd)
{
    if (!ft_strncmp(cmd, "echo ", 4))
        ft_echo(cmd);
    else
    {
        all->command_argv = ft_setsplit(cmd, " ");
        ft_execution(all);
        ft_free_split(all->command_argv);
    }
}
static int ft_strlen_c(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] != c && str[i])
		i++;
	return (i);
}

char	*get_line_c(char *line, int *i, char c)
{
	int		k;
	int 	j;
	char	*res;

	j = *i;
	if (c == '\"')
		j++;
	if (!(res = (char *)malloc(sizeof(char) * (ft_strlen_c(&line[j], c) + 1))))
		return (NULL);
	k = 0;
	while (line[j] != c && line[j])
		res[k++] = line[j++];
	res[k] = '\0';
	*i = j;
	return (res);
}

void    get_commands(t_all *all, char *line, int i)
{
    char **cmds;
	int k;
	int q;

	cmds = (char **)malloc(sizeof(char *) * (ft_wordcount(line, " ")));
    k = 0;
	q = check_quotes(line);
	if (q % 2 != 0 && q != 0)
	{
    	write(2, "Syntax error\n", 13);
    	return ;
	}
	while (line[i] && line[i] != ';')
	{
		while (IS_SPACE(line[i]))
			i++;
		if (line[i] == '\"')
		{
			cmds[k] = get_line_c(line, &i, '\"');
			i++;
			printf("%s cmds %d k\n", cmds[k], k);
			k++;
			continue ;
		}
		if (line[i] != ' ' && line[i] != '\"' && line[i] != ';')
		{
			cmds[k] = get_line_c(line, &i, ' ');
			printf("%s cmds %d k\n", cmds[k], k);
			k++;
			continue;
		}
	}
	if (line[i] == ';')
	{
		i++;
		get_commands(all, line, i);
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
	get_commands(all, line, 0);
}

void	no_interrupt(int signal_no)
{
	if (signal_no == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
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

	init_all(&all, env);
	all->av = av;
	signal(SIGQUIT, no_interrupt);
	while (1)
	{
		print_prompt(1);
		signal(SIGINT, no_interrupt);
		get_input(all);
	}
	return (EXIT_SUCCESS);
}