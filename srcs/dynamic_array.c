

#include "minishell.h"



void	delete_one_by_key(struct s_array **array, char *deleted_elem)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i < (*array)->current_size)
	{
		if (flag == 0 && ft_strncmp((*array)->str[i], deleted_elem, ft_strlen(deleted_elem)) == 0)
		{
			flag = 1;
			free((*array)->str[i]);
			break;
		}
		i++;
	}
	while ((*array)->str[i] && i < (*array)->current_size - 1)
	{
		(*array)->str[i] = (*array)->str[i + 1];
		i++;
	}
	if (flag == 1)
	{
		(*array)->str[(*array)->current_size - 1] = NULL;
		(*array)->current_size--;
	}
}

/*!
** \param size - number by how much to increase
*/

void resize(t_array **array, int size)
{
	char **str;
	int i;

	i = 0;
	if (size < 1 || size < (*array)->allocated_size - (*array)->current_size)
		return;
	if (!(str = (char **)ft_calloc(((*array)->current_size + size),
								   sizeof(char *))))
		return;
	(*array)->allocated_size = (*array)->current_size + size;
	while (i < (*array)->current_size)
	{
		str[i] = ft_strdup((*array)->str[i]);
		i++;
	}
	i = 0;
	while (i < (*array)->current_size)
	{
		free((*array)->str[i]);
		i++;
	}
	free((*array)->str);
	(*array)->str = str;
}

void	push_back(t_array **array, char *new)
{
	if ((*array)->current_size == (*array)->allocated_size)
		resize(array, 5);
	(*array)->str[(*array)->current_size++] = ft_strdup(new);
}

void print_array(t_array *array)
{
	int i;

	i = 0;
	ft_putstr_fd("array->current_size = ", 1);
	ft_putnbr_fd(array->current_size, 1);
	ft_putendl_fd("", 1);
	ft_putstr_fd("array->allocated_size = ", 1);
	ft_putnbr_fd(array->allocated_size, 1);
	ft_putendl_fd("", 1);
	while (i < array->current_size)
	{
		ft_putendl_fd(array->str[i], 1);
		i++;
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
	(*array)->clear = clear;
	printf("array inited\n");
}