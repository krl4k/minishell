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

static int ft_strlen_c(char *str, char q)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == q && str[i - 1] != '\\')
			return (i);
		i++;
	}
	if (str[i] != q)
		return (0);
	return (i);
}

void *syntax_error(void)
{
	write(1, "Syntax error\n", 13);
	return (NULL);
}

char	*get_in_quotes(char *line, int *i)
{
	char	*res;
	char	q;
	int		size;
	int		k;
	int 	j;

	q = line[*i];
	j = *i + 1;
	k = 0;
	if (!(size = ft_strlen_c(&line[j], q)))
		return (syntax_error());
	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (line[j] != q && line[j])
		res[k++] = line[j++];
	res[k] = '\0';
	*i = j + 1;
	return (res);
}
