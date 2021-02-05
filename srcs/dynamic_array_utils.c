/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:20:54 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/05 18:20:55 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_array_strs(t_array *array, int i)
{
	free((array)->str[i]);
	free((array)->key[i]);
	free((array)->value[i]);
}

static void		re_init(t_array *array, char **str, char **keys, char **values)
{
	free((array)->str);
	free((array)->key);
	free((array)->value);
	(array)->str = str;
	(array)->key = keys;
	(array)->value = values;
}

static void		resize_copy(t_array *a, char **str, char **keys, char **values)
{
	int i;

	i = 0;
	while (i < (a)->current_size)
	{
		str[i] = ft_strdup((a)->str[i]);
		keys[i] = ft_strdup((a)->key[i]);
		values[i] = ft_strdup((a)->value[i]);
		i++;
	}
}

void			resize(t_array *a, int size)
{
	char	**str;
	char	**keys;
	char	**values;
	int		i;

	i = 0;
	if (size < 1 || size < (a)->allocated_size - (a)->current_size)
		return ;
	if ((!(str = (char **)ft_calloc(a->current_size + size, sizeof(char *))))
	|| (!(keys = (char **)ft_calloc(a->current_size + size, sizeof(char *))))
	|| (!(values = (char **)ft_calloc(a->current_size + size, sizeof(char *)))))
		return ;
	(a)->allocated_size = (a)->current_size + size;
	resize_copy(a, str, keys, values);
	while (i < (a)->current_size)
	{
		free_array_strs(a, i);
		i++;
	}
	re_init(a, str, keys, values);
}
