#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../srcs/libft/libft.h"


void *ft_realloc(void *p, size_t p_size, size_t n_size)
{
	void *new;

	if (!p)
		return (NULL);
	if (!(new = (char *)calloc(n_size, sizeof(char))))
	{
		free(p);
		return (NULL);
	}
	ft_memcpy(new, p, p_size < n_size ? p_size : n_size);
	free(p);
	return (new);
}

int main()
{
	char n;
	char *word = (char *) malloc(1);
	int i = 0;
	int cur_size = 1;
	while ((n = getchar()) != '\n')
	{
		word = ft_realloc(word, cur_size, cur_size + 1);
		word[i] = n;
		cur_size++;
		i++;
	}
	printf("wprd = %s\n", word);
}