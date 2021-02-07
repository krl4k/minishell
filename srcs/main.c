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

/*
** return index of sep, or index of end elem
*/

int found_sep_pos(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], ";") == 0)
		{
			printf("array[%d] = %s\n" ,i,array[i]);
			return (i);
		}
		i++;
	}
	return (i);
}

int count_sep(char **array)
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

void 	sep_semicolon(t_all *all)
{
//	printf("-------------------------------------------------------------\n");
	int i;
	int j;
	int k;

	i = 0;
	k = 0;

	for (int l = 0; all->tmp[l]; l++)
	{
		printf("tmp[%d] = %s\n", l, all->tmp[l]);
	}

	int c_sep = count_sep(all->tmp);
//	printf("c_sep = %d\n", c_sep);
	j = 0;
	while (j < c_sep && all->tmp[k])
	{
//		printf("-------------------------------------------------------------\n");
		i = 0;
		int pos_sep = found_sep_pos(&all->tmp[k]);
//		printf("pos ; = %d\n", pos_sep);
		if (!(all->command_argv = (char **) ft_calloc(pos_sep + 1, sizeof(char *))))
			return;
		while (all->tmp[k] && (ft_strcmp(all->tmp[k], ";") !=0) && i < pos_sep)
		{
			all->command_argv[i] = ft_strdup(all->tmp[k]);
//			free(all->tmp[k]);
			k++;
			i++;
		}
		if (all->tmp[k] && ft_strcmp(all->tmp[k], ";") == 0)
		{
//			printf("is sep!!!\n");
			k++;
		}
		all->command_argv[i] = NULL;
//		for (int l = 0; all->command_argv[l]; l++)
//		{
//			printf("cmd_argv[%d] = %s\n", l, all->command_argv[l]);
//		}
		ft_execution(all);
//		printf("-------------------------------------------------------------\n");

		for (int l = 0; all->command_argv[l]; l++)
		{
			free(all->command_argv[l]);
			all->command_argv[l] = NULL;
		}
		free(all->command_argv);
	}

	int m = 0;
	while (all->tmp[m])
	{
		if (all->tmp[m])
		{
			free(all->tmp[m]);
			all->tmp[m] = NULL;
		}
		m++;
	}
	if (all->tmp)
		free(all->tmp);

//	while (all->tmp[k])
//	{
//		if (!(all->command_argv = (char **)ft_calloc(sizeof(char *), arr_size(&all->tmp[k]) + 1)))
//			return ;
//		if (!ft_strncmp(all->tmp[k], ";", ft_strlen(all->tmp[k])))
//			k++;
//		j = 0;
//		while (all->tmp[k] && ft_strcmp(all->tmp[k], ";"))
//		{
//			all->command_argv[j] = ft_strdup(all->tmp[k]);
//			printf("%s args %s tmp\n", all->command_argv[j], all->tmp[k]);
//			j++;
//			k++;
//		}
//		all->command_argv[j] = NULL;
//		ft_execution(all);
//		ft_free_split(all->command_argv);
//	}
}

void    get_commands(t_all *all, char *line)
{
	int i = 0;
	if (!(all->tmp = (char **)ft_calloc(sizeof(char *), 1)))
		return ;
	if (!parse_line(line, all))
	{
		free(line);
		return;
	}
	free(line);
	sep_semicolon(all);
//	while (cmd[i])
//		printf("%s\n", cmd[i++]);
//	ft_free_split(all->tmp);
}
/*!
** \brief return command and argument for execute func
** \todo parser and validate
** \warning you risk make shit
*/

char	*get_input(void)
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
		return (NULL);
	}
	return (input);
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
		//get_input(all);
		all->input = get_input();
		get_commands(all, all->input);
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