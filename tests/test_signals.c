#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

#include "../srcs/libft/libft.h"

/*!
 * От пользователя - с клавиатуры терминала можно нажимом некоторых клавиш послать сигналы SIGINT и SIGQUIT.
 * Собственно, сигнал посылается драйвером терминала при получении им с клавиатуры определенных символов.
 * Так можно прервать зациклившуюся или надоевшую программу.
 */


void handler(int sig_num)
{
	printf("sigabort!\n");
	exit(errno);
}

void ctrl_c(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		write(1, "\n>", 2);
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

void exec(char **av, char **env)
{
	pid_t pid;

	signal(SIGINT, ctrl_c_cat);
	signal(SIGQUIT, ctrl_slash_cat);
	int status;
	if ((pid = fork()) < 0)
		perror("exec error!");
	if (pid == 0)
	{
//		signal(SIGINT, SIG_DFL);

		status = execve("/bin/cat", av, env);
		exit(status);
	}
	else
	{
		wait(&status);
	}
}

int main(int ac, char **av, char **env)
{
//	write(1, ">", 1);
//	signal(SIGQUIT, ctrl_d);
//	signal(SIGILL, ctrl_slash);
	int fork = 0;
	while (1)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_slash);
		write(1, ">", 1);
		char *str;
		get_next_line(0, &str);
		if (strcmp(str, "cat") == 0)
		{
//			signal(SIGINT, ctrl_c_cat);
//			signal(SIGQUIT, ctrl_slash_cat);
			exec(av, env);
//			signal(SIGINT, ctrl_c);
		}
		else
			printf("%s\n", str);
	}
	return (0);
}