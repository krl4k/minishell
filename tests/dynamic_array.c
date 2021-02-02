#include <stdlib.h>
#include <stdio.h>
#include "../srcs/libft/libft.h"

/*!
** t_array *array;
** init_array(&array, size);
**
*/


typedef struct	s_array
{
	char		**str;
	int			current_size;
	int			allocated_size;
	void		(*clear)(struct  s_array **array);
	void		(*resize)(struct s_array *array, int size);
	void		(*delete_one)(struct s_array *array, int pos);
	void		(*delete_one_by_key)(struct s_array *array, char *deleted_elem);
	void		(*push_back)(struct s_array *array, char *new);
//	void		(*copy)(struct s_array **array, char **new_array);
	void		(*print_array)(struct s_array *array);
	void		(*print_info)(struct s_array *array);
}				t_array;


void	delete_one_by_key(struct s_array *array, char *deleted_elem)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i <= (array)->current_size)
	{
		if (flag == 0 && ft_is_equal(array->str[i], deleted_elem) == 0)
		{
			flag = 1;
			free((array)->str[i]);
			break;
		}
		i++;
	}
	while ((array)->str[i] && i < (array)->current_size - 1)
	{
		(array)->str[i] = (array)->str[i + 1];
		i++;
	}
	if (flag == 1)
	{
		(array)->str[(array)->current_size - 1] = NULL;
		(array)->current_size--;
	}
	if ((array)->current_size < 0)
		(array)->current_size = 0;
}

/*!
** \param size - number by how much to increase
*/

void resize(t_array *array, int size)
{
	char **str;
	int i;

	i = 0;
	if (size < 1 || size < (array)->allocated_size - (array)->current_size)
		return;
	if (!(str = (char **)ft_calloc(((array)->current_size + size),
				sizeof(char *))))
		return;
	(array)->allocated_size = (array)->current_size + size;
	while (i < (array)->current_size)
	{
		str[i] = ft_strdup((array)->str[i]);
		i++;
	}
	i = 0;
	while (i < (array)->current_size)
	{
		free((array)->str[i]);
		i++;
	}
	free((array)->str);
	(array)->str = str;
}

//void	push_back(t_array **array, char *new)
//{
//	if ((*array)->current_size == (*array)->allocated_size)
//		resize(array, 5);
//	(*array)->str[(*array)->current_size++] = ft_strdup(new);
//}

void	push_back(t_array *array, char *new)
{
	if ((array)->current_size == (array)->allocated_size)
		resize(array, 5);
	(array)->str[(array)->current_size++] = ft_strdup(new);
}


void print_array(t_array *array)
{
	int i;

	i = 0;
	while (i < array->current_size)
	{
		ft_putendl_fd(array->str[i], 1);
		i++;
	}
}

void print_info(t_array *array)
{
	if (array)
	{
		ft_putstr_fd("array->current_size = ", 1);
		ft_putnbr_fd(array->current_size, 1);
		ft_putendl_fd("", 1);
		ft_putstr_fd("array->allocated_size = ", 1);
		ft_putnbr_fd(array->allocated_size, 1);
		ft_putendl_fd("", 1);
	}
}


void	clear(struct  s_array **array)
{
	int i;

	i = 0;
	while (i < (*array)->allocated_size)
	{
		free((*array)->str[i]);
		i++;
	}
	(*array)->allocated_size = 0;
	(*array)->current_size = 0;
	free((*array)->str);
	free(*array);
	(*array)= NULL;
}


void init_array(t_array **array, int size)
{
	if (size < 1)
		return;
	if (!(*array = (t_array *)malloc(sizeof(t_array))))
		return;
	(*array)->current_size = 0;
	(*array)->allocated_size = size + 5;
	if (!(((*array)->str = (char **)ft_calloc(((*array)->allocated_size), sizeof(char *)))))
		return;
	(*array)->print_array = print_array;
	(*array)->push_back = push_back;
	(*array)->resize = resize;
	(*array)->delete_one_by_key = delete_one_by_key;
	(*array)->print_array = print_array;
	(*array)->print_info = print_info;
	(*array)->clear = clear;

}

int main(int argc, char **argv, char **env)
{
	t_array *array;
	int size = 5;
	init_array(&array, size);
	array->print_info(array);

	array->push_back(array, "1");
	array->push_back(array, "2");
	array->push_back(array, "3");
	array->push_back(array, "4");
	array->push_back(array, "5");
	array->push_back(array, "6");
	array->push_back(array, "7");

	array->delete_one_by_key(array, "1");
	array->delete_one_by_key(array, "2");
	array->delete_one_by_key(array, "3");
	array->delete_one_by_key(array, "4");
	array->delete_one_by_key(array, "5");
	array->delete_one_by_key(array, "6");
	array->delete_one_by_key(array, "7");
	array->delete_one_by_key(array, "7");
	array->delete_one_by_key(array, "7");
	array->delete_one_by_key(array, "7");

//	array->resize(&array, 4);
	array->push_back(array, "1");
	array->push_back(array, "2");
	array->push_back(array, "3");
	array->push_back(array, "4");
	array->push_back(array, "5");
	array->push_back(array, "6");
	array->push_back(array, "7");

	array->print_array(array);
	array->print_info(array);
//	array->print_array(array);
//	array->print_info(array);

	array->clear(&array);
//	while (1);
	return 0;
}
