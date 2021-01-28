#include <stdlib.h>
#include <stdio.h>
#include "../srcs/libft/libft.h"

void delete_one(char **array, int count, int pos)
{
	int i = 0;

	while ((array)[i])
	{
		printf("copy = %s\n", array[i]);
		i++;
	}
	free(array[pos]);
	while (array[pos])
	{
		array[pos] = array[pos + 1];
		pos++;
	}
	array[pos] = NULL;
	array  = array;
//	int new_count = count - 1;
//	char **new_array = (char **)malloc(sizeof(char *) * (new_count  + 1));
//	int i = 0;
//
//	while (i < pos)
//	{
//		printf("copy = %s\n", *array[i]);
//		new_array[i] = ft_strdup(*array[i]);
//		i++;
//	}
//	if (*array[i])
//		i++;
//		free(array[i]);
//	while (array[i + 1])
//	{
//		printf("copy = %s\n", array[i+1]);
//		new_array[i] =  ft_strdup(*array[i + 1]);
//		i++;
//	}
//	array[i] = NULL;
//	new_array[i] = NULL;
//	i = 0;
//	while (i < pos)
//	{
//		free(array[i]);
//		i++;
//	}
//	free(array);
//	*array = new_array;
}

int main(int argc, char **argv, char **env)
{
	char **array = (char **)malloc(sizeof(char *) * 7);
	array[0] = ft_strdup("a");
	array[1] = ft_strdup("b");
	array[2] = ft_strdup("c");
	array[3] = ft_strdup("d");
	array[4] = ft_strdup("e");
	array[5] = ft_strdup("f");
	array[6] = ft_strdup("g");
	array[7] = NULL;

	int i = -1;
	while (array[++i])
		printf("array[%d] = %s\n", i, array[i]);

	i = 0;
	int pos = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "d", 1) ==  0)
			break;
		pos++;
		i++;
	}
	printf("\npos = %d, %s\n\n", pos, array[pos]);

	delete_one(array, 7, pos);
	i = -1;
	while (array[++i])
		printf("array[%d] = %s\n", i, array[i]);

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	while (1);

	return 0;
}
