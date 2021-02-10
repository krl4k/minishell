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
		if (!ret)
		{
			if (!(*i))
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
	char	*input;

	i = 0;
	input = (char *)malloc(sizeof(char));
	ret = get_str(&input, &i);
	if (!ret)
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
//	if(!ret)
//	{
//		free(input);
//		ft_exit(NULL);
//		return (NULL);
//	}
	return (input);
}


