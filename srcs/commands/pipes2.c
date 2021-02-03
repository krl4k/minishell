
#include "minishell.h"


void init_handler_pipes(t_all *all)
{
	all->in_path = NULL;
	all->out_path = NULL;
	all->input_redir_flag = 0;
	all->output_redir_flag = 0;
	all->append_redir_flag = 0;
	all->pipes = 0;

	if (!(all->arg_location = (int *) malloc(sizeof(int) * count_command(all))))
		exit(2);
}

void 	free_handler_pipes(t_all *all)
{
	if (all->in_path)
		free(all->in_path);
	if (all->out_path)
		free(all->out_path);
	if (all->arg_location)
		free(all->arg_location);
}



int execute_commands(t_all *all)
{
	int index;
	pid_t pid;

	index = 0;
	while (index <= all->pipes)
	{
		if (pipes > 0 && index != all->pipes)
		{
			/* if user has entered multiple commands with '|' */
			if (pipe(all->r_pipe) < 0)
				perror("pipe() error");
		}
		if ((pid = fork()) < 0)
			perror("fork() error");
		if (pid == 0)
		{

			if ((index == 0) && (all->input_redir_flag == 1))
			{
				input_redir_init(all, index);
//				if ((all->input_file_descriptor = open(all->in_path, O_RDONLY)) < 0)
//					perror("open()");
//				if (all->input_file_descriptor == -1)
//				{
//					perror("input file failed to open\n");
//					return (EXIT_FAILURE);
//				}
//				close(READ);
//				dup(all->input_file_descriptor);
//				close(all->input_file_descriptor);
			}
			/* end of input redirection management */
			if ((index == all->pipes) && (all->output_redir_flag == 1))
			{
				//printf("DEBUG: here we should be about to create our output file\n");
				output_redir_init(all, index);
//				if ((all->output_file_descriptor = open(all->out_path, O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
//					perror("open()");
//				if (all->output_file_descriptor < 0)
//				{
//					perror("output file failed to open\n");
//					return (EXIT_FAILURE);
//				}
//				close(WRITE);
//				dup(all->output_file_descriptor);
//				close(all->output_file_descriptor);
			}
			if ((index == all->pipes) && (all->append_redir_flag == 1))
			{
				append_redir_init(all, index);
//				all->output_file_descriptor = creat(all->out_path, 0700);
//				if ((all->output_file_descriptor = open(all->out_path, O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
//					perror("open()");
//				if (all->output_file_descriptor < 0)
//				{
//					perror("output file failed to open\n");
//					return (EXIT_FAILURE);
//				}
//				close(WRITE);
//				dup(all->output_file_descriptor);
//				close(all->output_file_descriptor);
			}
			/* end of output redirection management */
			if (all->pipes > 0)
			{
				pipes_fd_init(all, index);

//				if (index == 0)
//				{
//					close(WRITE);
//					dup(all->r_pipe[WRITE]);
//					close(all->r_pipe[WRITE]);
//					close(all->r_pipe[READ]);
//				}
//				else if (index < all->pipes)
//				{
//					close(READ);
//					dup(all->l_pipe[READ]);
//					close(all->l_pipe[READ]);
//					close(all->l_pipe[WRITE]);
//					close(WRITE);
//					dup(all->r_pipe[WRITE]);
//					close(all->r_pipe[READ]);
//					close(all->r_pipe[WRITE]);
//				} else
//				{
//					close(READ);
//					dup(all->l_pipe[READ]);
//					close(all->l_pipe[READ]);
//					close(all->l_pipe[WRITE]);
//				}
			}
			char *command = check_bin_func(all->command_argv[all->arg_location[index]]);
			if (!command)
				exit(3);
			execve(command, &all->command_argv[all->arg_location[index]], all->env_array->str);
			free(command);
			perror("execution of command failed\n");
		}
		else
		{
			if (index > 0)
			{
				close(all->l_pipe[READ]);
				close(all->l_pipe[WRITE]);
			}
			all->l_pipe[READ] = all->r_pipe[READ];
			all->l_pipe[WRITE] = all->r_pipe[WRITE];
			/* parent waits for child process to complete */
			wait(&all->status);
			if (WIFEXITED(all->status) != 0)
			{
				if (WEXITSTATUS(all->status) == 3)
				{
					ft_putstr_fd(PROMT_ERROR, 2);
					ft_putstr_fd(all->command_argv[0], 2);
					ft_putstr_fd(": ", 2);
					ft_putendl_fd("command not found", 2);
				}
			}
		}
		index++;
	}
	return (EXIT_SUCCESS);
}


/*!
** redir management
*/
void check_flags(t_all *all)
{
	int count;

	count = 0;
	while (all->command_argv[count])// != 0
	{
		if (ft_strcmp(all->command_argv[count], "|") == 0)
		{
			all->command_argv[count] = 0;
			all->arg_location[all->pipes + 1] = count + 1;
			++(all->pipes);
		}
		else if (ft_strcmp(all->command_argv[count], "<") == 0)
		{
			all->in_path = ft_strdup(all->command_argv[count + 1]);
			all->command_argv[count] = 0;
			all->input_redir_flag = 1;
		}
		else if (ft_strcmp(all->command_argv[count], ">") == 0)
		{
			all->out_path = ft_strdup(all->command_argv[count + 1]);
			all->command_argv[count] = 0;
			all->output_redir_flag = 1;
		}
		else if (ft_strcmp(all->command_argv[count], ">>") == 0)
		{
			all->out_path = ft_strdup(all->command_argv[count + 1]);
			all->command_argv[count] = 0;
			all->append_redir_flag = 1;
		}
		else
		{
			all->arg_location[count] = count;
		}
		++count;
	}
}

int pipes_work(t_all *all)
{
	int count;

	count = 0;
	for (int i = 0; all->command_argv[i]; ++i)
	{
		printf("cmd[%d] = %s\n", i, all->command_argv[i]);
	}
	init_handler_pipes(all);
	check_flags(all);

	printf("count	   pipes = %d\n", all->pipes);
	printf("flag input redir = %d\n", all->input_redir_flag);
	printf("flag outputredir = %d\n", all->output_redir_flag);
	printf("flag appnd redir = %d\n", all->append_redir_flag);
//	exit(0);
	/* eend of redir management*/
	execute_commands(all);
	free_handler_pipes(all);
	return (0);
}