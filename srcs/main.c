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


void print_prompt(int fd)
{
	char *prompt;

	prompt = "▓▒░(°◡°)░▒▓\0";
	ft_putstr_fd(prompt, fd);
}

int is_numeric(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		if (!ft_isdigit(cmd[i++]))
			return (0);
	return (1);
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

int		arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], ";"))
		i++;
	return (i);
}

void 	sep_semicolon(t_all *all)
{
	int 	i;
	int 	j;
	int 	k;

	i = 0;
	k = 0;
	while (all->tmp[k])
	{
		if (!(all->command_argv = (char **)ft_calloc(sizeof(char *), arr_size(&all->tmp[k]) + 1)))
			return ;
		if (!ft_strncmp(all->tmp[k], ";", ft_strlen(all->tmp[k])))
			k++;
		j = 0;
		while (all->tmp[k] && ft_strncmp(all->tmp[k], ";", ft_strlen(all->tmp[k])))
		{
			all->command_argv[j] = ft_strdup(all->tmp[k]);
			//printf("%s args %s tmp\n", all->command_argv[j], all->tmp[k]);
			j++;
			k++;
		}
		printf("before\n");
		ft_execution(all);
		printf("after\n");
		ft_free_split(all->command_argv);
	}
}

void    get_commands(t_all *all, char *line)
{
	int i = 0;
	if (!(all->tmp = (char **)ft_calloc(sizeof(char *), 2)))
		return ;
	if (!(all->tmp = parse_line(line, all->tmp)))
	{
		free(line);
		return;
	}
	printf("%s input\n", line);
	free(line);
	sep_semicolon(all);
//	while (cmd[i])
//		printf("%s\n", cmd[i++]);
	ft_free_split(all->tmp);
}
/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/

void get_input(t_all *all)
{
	int		ret;
	int		i;
	char	c;
	char	*input;


	i = 0;
	input = ft_strdup("");
	while ((ret = read(0, &c, 1)) > 0 && c != '\n')
	{
		input[i++] = c;
		input = ft_realloc(input, i, i + 1);
	}
	input[i] = '\0';
	if(!ret)
	{
		free(input);
		ft_exit(NULL);
	}
	get_commands(all, input);
}

/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/


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
//	signal(SIGQUIT, no_interrupt);
	while (1)
	{
		signals_init(1);
		print_prompt(1);
//		signal(SIGINT, no_interrupt);
		get_input(all);
//		while (all->command_argv[i])
//		{
//			free(all->command_argv[i]);
//			all->command_argv[i] = NULL;
//			i++;
//		}
//		free(all->command_argv);
	}
	return (EXIT_SUCCESS);
}