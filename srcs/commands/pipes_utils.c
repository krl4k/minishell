#include "minishell.h"

/*!
** "<" input redirect
*/

int input_redir(t_all *all, int index)
{
	if ((index == 0) && (all->input_redir_flag == 1))
	{
		if ((all->input_file_descriptor = open(all->in_path, O_RDONLY)) < 0)
			perror("open()");
		if (all->input_file_descriptor == -1)
		{
			perror("input file failed to open\n");
			return (EXIT_FAILURE);
		}
		close(READ);
		dup(all->input_file_descriptor);
		close(all->input_file_descriptor);
	}
	return (EXIT_SUCCESS);
}



/*!
** ">" output redirect
*/