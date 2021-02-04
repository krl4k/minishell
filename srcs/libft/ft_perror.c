#include "libft.h"

void ft_perror(char *s)
{
	if (!s)
		return;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}
