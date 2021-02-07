# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../srcs/libft/libft.h"


void ft_perror(char *s)
{
	if (!s)
		return;
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int main()
{
	int fd;

	if ((fd = open("fjksd", O_RDONLY)))
		perror("open()");

	printf("lol\n");
}