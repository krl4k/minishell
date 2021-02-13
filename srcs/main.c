/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*   									              +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/12 20:39:14 by mwinter          ###   ########.fr       */
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

int		arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], ";"))
		i++;
	return (i);
}

int		found_sep_pos(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], ";") == 0)
			return (i);
		i++;
	}
	return (i);
}

int		count_sep(char **array)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], ";") == 0)
			count++;
		i++;
	}
	return (count + 1);
}

//void	sep_semicolon(t_all *all)
//{
//	int i;
//	int j;
//	int k;
//	int c_sep;
//	int pos_sep;
//
//	k = 0;
//	c_sep = count_sep(all->tmp);
//	j = 0;
//	while (j < c_sep && all->tmp[k])
//	{
//		i = 0;
//		pos_sep = found_sep_pos(&all->tmp[k]);
//		if (!(all->command_argv = (char **) ft_calloc(pos_sep + 1, sizeof(char *))))
//			return;
//		while (all->tmp[k] && (ft_strcmp(all->tmp[k], ";") !=0) && i < pos_sep)
//		{
//			all->command_argv[i] = ft_strdup(all->tmp[k]);
//			k++;
//			i++;
//		}
//		if (all->tmp[k] && !ft_strcmp(all->tmp[k], ";"))
//			k++;
//		ft_execution(all);
//		ft_free_split(all->command_argv);
//	}
//	ft_free_split(all->tmp);
//}

void    get_commands(t_all *all, char *line)
{
	all->i = 0;
	while(line[all->i])
	{
		if (!(all->command_argv = (char **)ft_calloc(sizeof(char *), 2)))
			return ;
		if (!parse_line(line, all))
		{
			ft_free_split(all->command_argv);
			free(line);
			return;
		}
		if (check_controls(all))
			return ;
		ft_execution(all);
		ft_free_split(all->command_argv);
	}
	free(line);
//	if (check_controls(all))
//		return ;
//	sep_semicolon(all);
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
	(void)ac;
	t_all *all;

	init_all(&all, env);
	all->av = av;
	while (1)
	{
		signals_init(1);
		print_prompt(2);
		all->input = get_input();
		all->input = substitution_env(all);
		get_commands(all, all->input);
	}
	return (EXIT_SUCCESS);
}