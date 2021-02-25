/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:20:03 by fgrisell          #+#    #+#             */
/*   Updated: 2021/02/14 14:20:04 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

typedef struct	s_array
{
	char		**str;
	char		**key;
	char		**value;
	int			current_size;
	int			allocated_size;
	void		(*clear)(struct s_array **array);
	void		(*resize)(struct s_array *array, int size);
	void		(*delete_one)(struct s_array *array, int pos);
	void		(*delete_one_by_key)(struct s_array *array, char *deleted_elem);
	void		(*push_back)(struct s_array *array, char *new);
	void		(*print_array)(struct s_array *array);
}				t_array;

void			init_array(t_array **array, int size);
void			resize(t_array *array, int size);
void			free_array_strs(t_array *array, int i);
#endif
