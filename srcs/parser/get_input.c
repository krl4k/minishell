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
/*
int		size_arr(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int is_numeric(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
		if (!ft_isdigit(cmd[i++]))
			return (0);
	return (1);
}*/

/*!
** \brief return command and argument for execute func
** \warning you risk make shit
*/
char	*get_input(void)
{
	int		ret;
	int		i;
	char	c;
	char	*input;


	i = 0;
	input = (char *)malloc(sizeof(char));
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
/*
int main()
{
	char *line;

		line = get_input();
		printf("%s\n", line);
		free(line);
}*/

