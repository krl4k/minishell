

#include "minishell.h"

//
//static void sort_vars(char **env, int count)
//{
//	int i;
//	int sorted;
//	char *temp;
//
//	sorted = 0;
//	while (!sorted)
//	{
//		i = 0;
//		sorted = 1;
//		while (i < count - 1)
//		{
//			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
//			{
//				temp = env[i];
//				env[i] = env[i + 1];
//				env[i + 1] = temp;
//				sorted = 0;
//			}
//			i++;
//		}
//	}
//}


static void sort_vars(char **env, int count, int *index)
{
	int i;
	int sorted;
	int temp;
	char *tmp;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (i < count - 1)
		{
			if(ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = index[i];
				index[i] = index[i + 1];
				index[i + 1] = temp;
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
}

void write_export(t_array *array, int i)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(array->key[i], 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(array->value[i], 1);
	ft_putendl_fd("\"", 1);
}

void print_sort_envs(t_all *all, char **temp_env, int *env_index)
{
	int i;

	i = 0;
	while (i < all->env_array->current_size)
	{
		temp_env[i] = ft_strdup(all->env_array->str[i]);
		i++;
	}
	temp_env[i] = NULL;
	i = 0;
	while (i < all->env_array->current_size)
	{
		env_index[i] = i;
		i++;
	}
	sort_vars(temp_env, all->env_array->current_size, env_index);
	i = 0;
	while (i < all->env_array->current_size)
	{
		write_export(all->env_array, env_index[i]);
		i++;
	}
}

int ft_export_print_sort_env(t_all *all)
{
	char **temp_env;
	int *env_index;
	int i;

	i = 0;
	if(!(temp_env = (char **) ft_calloc(all->env_array->current_size + 1, sizeof(char *))))
		error_handler(1);
	if(!(env_index = (int *)ft_calloc((sizeof(int)),  all->env_array->current_size)))
		error_handler(1);
	print_sort_envs(all, temp_env, env_index);
	while (temp_env[i])//i < all->env_array->current_size &&
		free(temp_env[i++]);
	free(temp_env);
	free(env_index);
	return (0);
}