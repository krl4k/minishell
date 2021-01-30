#include <stdio.h>
#include <unistd.h>
#include "libft.h"

int main(int argc, char *argv[])
{
	//char *res;

	(void)argc;
	printf("%s\n", ft_strtrim(argv[1], "\""));
	return 0;
}
