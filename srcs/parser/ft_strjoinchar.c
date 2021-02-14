/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/13 20:34:17 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinchar(char *str, char c)
{
	char	*new;
	int		i;

	if (!str || !c)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}
