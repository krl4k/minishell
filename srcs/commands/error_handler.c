#include "minishell.h"

void error_handler(int type_error)
{
	if (type_error == 1)
		ft_putendl_fd("Malloc error!\n", 2);

	exit(errno);
}