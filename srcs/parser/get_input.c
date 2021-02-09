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

/*!
** \brief return command and argument for execute func
** \warning you risk make shit
*/

int get_str(char **input, int *i)
{
	int ret;
	char c;

	while (((ret = read(0, &c, 1)) != -1) && c != '\n')
	{
		if (ret == 0)
		{
			if (*i == 0)
				return (0);
			write(1, "  \b\b", 4);
		}
		else
		{
			*(*input + *i) = c;
			(*i)++;
			*input = ft_realloc(*input, (*i), (*i) + 1);
		}
	}
	*(*input + *i) = '\0';
	return ret;
}

char	*get_input(void)
{
	int		ret;
	int		i;
	char	c;
	char	*input;

	i = 0;
	input = (char *)malloc(sizeof(char));
//	while ((ret = read(0, &c, 1)) > 0 && c != '\n')
//	{
//		input[i++] = c;
//		input = ft_realloc(input, i, i + 1);
//	}
//	input[i] = '\0';
	ret = get_str(&input, &i);
//	printf("line = %s\n", input);
//	printf("ret = %d\n", ret);

//	while (1)
//	{
//		ret = get_str(&input, &i);
//		if (ret == 0)
//		{
//			if (i == 0)
//			{
//				write(1, "  \b\b", 4);
//				write(1, " exit\n", 6);
//				exit(0);
//			}
//		}
//	}



	if (ret == 0)
	{
		if (i == 0)
		{
			write(1, "  \b\b", 4);
			write(1, " exit\n", 6);
			exit(0);
		}
		else
		{
			get_str(&input, &i);
		}
	}
//	printf("\ntut\n");

//	ret = 1;
//	ret = get_str(input, &i);
//	printf("ret = %d", ret);
//	if (ret)
//	while (ret)
//	{
//		printf("i  = %d\n", i);
//		ret = get_str(input, &i);
//		if (i == 0)
//		{
//			write(1, "  \b\b", 4);
//			write(1, " exit\n", 6);
//			exit(0);
//		}
//	}

//	input[i] = '\0';
//	printf("tut1\n");
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

