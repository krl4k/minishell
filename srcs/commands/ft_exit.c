#include "minishell.h"

void    ft_exit(char **cmd)
{
	int ret;

	ret = 0;
	if (size_arr(cmd) > 2 && is_numeric(cmd[1]))
	{
		write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": ", 2);
		ft_putendl_fd("too many arguments", 2);
		g_exit_code = 1;
		return ;
	}
	if (cmd[1] && is_numeric(cmd[1]))
		ret = ft_atoi(cmd[1]);
	else if (cmd[1] && !is_numeric(cmd[1]))
	{
		write(2, PROMT_ERROR, ft_strlen(PROMT_ERROR));
		write(2, ": ", 2);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": ", 2);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": ", 2);
		ft_putendl_fd("numeric argument required", 2);
		ret = 255;
	}
	write(1, "exit\n", 5);
	ret = ret > 255 ? 255 : ret;
	ft_free_split(cmd);
	exit(ret);
}