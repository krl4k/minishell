

#include "minishell.h"

static void free_array_strs(t_array *array, int i)
{
	free((array)->str[i]);
	free((array)->key[i]);
	free((array)->value[i]);
}

void	delete_one_by_key(struct s_array *array, char *deleted_elem)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i < (array)->current_size)
	{
		if (flag == 0 && ft_strncmp((array)->key[i], deleted_elem, ft_strlen(deleted_elem)) == 0)
		{
			flag = 1;
			free_array_strs(array, i);
			break;
		}
		i++;
	}
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

/*!
** \param size - number by how much to increase
*/

void resize(t_array *array, int size)
{
	char **str;
	char **keys;
	char **values;
	int i;

	i = 0;
	if (size < 1 || size < (array)->allocated_size - (array)->current_size)
		return;
	if ((!(str = (char **)ft_calloc(((array)->current_size + size),sizeof(char *))))
	||(!(keys = (char **)ft_calloc(((array)->current_size + size),sizeof(char *))))
	||(!(values = (char **)ft_calloc(((array)->current_size + size),sizeof(char *)))))
		return;
	(array)->allocated_size = (array)->current_size + size;
	while (i < (array)->current_size)
	{
		str[i] = ft_strdup((array)->str[i]);
		keys[i] = ft_strdup((array)->key[i]);
		values[i] = ft_strdup((array)->value[i]);
		i++;
	}
	i = 0;
	while (i < (array)->current_size)
	{
		free_array_strs(array, i);
		i++;
	}
	free((array)->str);
	free((array)->key);
	free((array)->value);
	(array)->str = str;
	(array)->key = keys;
	(array)->value = values;
}

void	push_back(t_array *array, char *new)
{
	int i;

	i = 0;
//	printf("push_back new = %s\n", new);
	if ((array)->current_size == (array)->allocated_size)
		resize(array, 5);
	(array)->str[(array)->current_size] = ft_strdup(new);
	while (new[i] && new[i] != '=')
		i++;
	(array)->key[(array)->current_size] = ft_substr(array->str[array->current_size], 0, i);
	char *r;
	if ((r = (char *)ft_strchr(new, '=')) != NULL)
	{
		r++;
		(array)->value[(array)->current_size] = ft_substr(r, 0, ft_strlen(r));
	}
	else
		(array)->value[(array)->current_size] = ft_strdup("");
//	array->str[array->current_size + 1] = NULL;
//	array->key[array->current_size + 1] = NULL;
//	array->value[array->current_size + 1] = NULL;
	(array)->current_size++;

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
	if (!(((*array)->key = (char **)ft_calloc(((*array)->allocated_size), sizeof(char *)))))
		return;
	if (!(((*array)->value = (char **)ft_calloc(((*array)->allocated_size), sizeof(char *)))))
		return;
	(*array)->print_array = print_array;
	(*array)->push_back = push_back;
	(*array)->resize = resize;
	(*array)->delete_one_by_key = delete_one_by_key;
	(*array)->print_array = print_array;
	(*array)->clear = clear;
//	printf("array inited\n");
}