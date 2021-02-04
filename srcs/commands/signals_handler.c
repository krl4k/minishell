
#include "minishell.h"

void ctrl_c(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		print_prompt(1);
		signal(SIGINT, ctrl_c);
	}
//	write(1, ">", 1);

}

void ctrl_c_cat(int sig_num)
{
	write(1, "\n", 1);
	signal(SIGINT, ctrl_c_cat);
}

void ctrl_slash(int fork)
{
	write(1, "\b\b  \b\b", 6);
	signal(SIGQUIT, ctrl_slash);
}


void ctrl_slash_cat(int fork)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: 3\n", 10);
	signal(SIGQUIT, ctrl_slash_cat);
}

void signals_init(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
	}
	if (mode == 2)
	{
		signal(SIGINT, ctrl_c_cat);
		signal(SIGQUIT, ctrl_slash_cat);
	}
}