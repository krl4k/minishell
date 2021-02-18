/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:42:35 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/14 18:18:16 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code = 0;

void	print_prompt(int fd)
{
	char *prompt;

	prompt = "▓▒░(°◡°)░▒▓\0";
	ft_putstr_fd(prompt, fd);
}

int		is_numeric(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		if (!ft_isdigit(cmd[i++]))
			return (0);
	return (1);
}

int		count_argv(t_all *all)
{
    int i;

    i = 0;
    while (all->command_argv[i])
        i++;
    return (i);
}

/*
** set all->command_argv (command_argv this is a null-terminated array
** of strings)
** \authors fgrisell and mwinter
** \version Temporary
** \example FIRST ARGUMENT: BIN FILE or BUILTIN COMMAND - argv[0] = /bin/ls
** \example FLAGS	(n > 0 && n < argc) - argv[n] = "-la" (flag)(optional)
** \example LAST ARGUMENT: argv[argc] = NULL;
** \warning The last argument should always be NULL!
*/

void	get_commands(t_all *all, char *line)
{
	all->i = 0;
	while (all->i < 1024)
	    all->flag[all->i++] = 0;
	all->i = 0;
	while (line[all->i])
	{
		if (!(all->command_argv = (char **)ft_calloc(sizeof(char *), 2)))
			return ;
		if (!parse_line(line, all))
		{
			ft_free_split(all->command_argv);
			free(line);
			return ;
		}
        all->count_argv = count_argv(all);
        if (!check_controls(all))
            ft_execution(all);
		ft_free_split_count(all->command_argv, all->count_argv);
	}
	free(line);
}

/*
** Entrypoint in minishell
** @param	ac	arguments count
** @param	av	arguments
** @param	env	environment variables
** @return	0 if success
*/

int		main(int ac, char **av, char **env)
{
	t_all *all;

	(void)ac;
	(void)av;
	init_all(&all, env);
	while (1)
	{
		signals_init(1);
		print_prompt(2);
		all->input = get_input();
		substitution_env(all);
	}
	return (EXIT_SUCCESS);
}
