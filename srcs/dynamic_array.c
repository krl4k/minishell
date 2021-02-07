/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 18:17:22 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/05 18:17:24 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_after_deleted(t_array *array, int i, int flag)
{
	while ((array)->str[i] && i < (array)->current_size - 1)
	{
		(array)->str[i] = (array)->str[i + 1];
		(array)->key[i] = (array)->key[i + 1];
		(array)->value[i] = (array)->value[i + 1];
		i++;
	}
	if (flag == 1)
	{
		(array)->str[(array)->current_size - 1] = NULL;
		(array)->key[(array)->current_size - 1] = NULL;
		(array)->value[(array)->current_size - 1] = NULL;
		(array)->current_size--;
	}
}

void	delete_one_by_key(struct s_array *array, char *deleted_elem)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i <= (array)->current_size)
	{
		if (flag == 0 && ft_strncmp((array)->key[i], deleted_elem,
		ft_strlen(deleted_elem)) == 0)
		{
			flag = 1;
			free_array_strs(array, i);
			break ;
		}
		i++;
	}
	copy_after_deleted(array, i, flag);
	if ((array)->current_size < 0)
		(array)->current_size = 0;
}

/*
** \param size - number by how much to increase
*/

void	push_back(t_array *ar, char *new)
{
	int		i;
	char	*r;

	i = 0;
	if ((ar)->current_size == (ar)->allocated_size)
		resize(ar, 20);
	(ar)->str[(ar)->current_size] = ft_strdup(new);
	while (new[i] && new[i] != '=')
		i++;
	(ar)->key[(ar)->current_size] = ft_substr(ar->str[ar->current_size], 0, i);
	if ((r = (char *)ft_strchr(new, '=')) != NULL)
	{
		r++;
		(ar)->value[(ar)->current_size] = ft_substr(r, 0, ft_strlen(r));
	}
	else
		(ar)->value[(ar)->current_size] = ft_strdup("");
	(ar)->current_size++;
}

void	clear(struct s_array **array)
{
	int i;

	i = 0;
	while (i < (*array)->allocated_size)
	{
		free((*array)->str[i]);
		free((*array)->key[i]);
		free((*array)->value[i]);
		i++;
	}
	(*array)->allocated_size = 0;
	(*array)->current_size = 0;
	free((*array)->str);
	free((*array)->key);
	free((*array)->value);
	free(*array);
	(*array) = NULL;
}

void	init_array(t_array **array, int size)
{
	int aloc_size;

	if (size < 1)
		return ;
	if (!(*array = (t_array *)malloc(sizeof(t_array))))
		return ;
	(*array)->current_size = 0;
	(*array)->allocated_size = size + 5;
	aloc_size = (*array)->allocated_size;
	if (!(((*array)->str = (char **)ft_calloc(aloc_size, sizeof(char *)))))
		return ;
	if (!(((*array)->key = (char **)ft_calloc(aloc_size, sizeof(char *)))))
		return ;
	if (!(((*array)->value = (char **)ft_calloc(aloc_size, sizeof(char *)))))
		return ;
	(*array)->push_back = push_back;
	(*array)->resize = resize;
	(*array)->delete_one_by_key = delete_one_by_key;
	(*array)->clear = clear;
}
