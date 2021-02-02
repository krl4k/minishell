#include "libft.h"

int ft_is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) != strlen(s2))
		return (0);
	if (ft_strcmp(s1, s2) != 0)
		return (0);
	return (1);
}