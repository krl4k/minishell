#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../srcs/libft/libft.h"

#ifndef READ
#define READ 0
#endif

#ifndef WRITE
#define WRITE 1
#endif

static int is_prefix_bin(char *line)
{
	if (strcmp("/bin/", line) == 0)
		return (1);
	return (0);
}

char *check_bin_func(char *cmd)
{
	char *command;
	int i;
	int flag;

	static char *bin_array[]= {"cp", "df", "hostname", "link", "mv"," rm", "stty", "test", "bash","csh", "echo",
							   "kill","ln","pax","rmdir", "sync","unlink", "cat","date","ed", "ksh","ls","ps","sh","syslog.py",
							   "wait4path", "chmod","dd", "expr","launchctl","mkdir","pwd","sleep", "tcsh","zsh", NULL};
	flag = 0;
	i = 0;
	command = strdup(cmd);
	while (bin_array[i])
	{
		if (strcmp(cmd, bin_array[i]) == 0)
			flag = 1;
		i++;
	}
	if (flag)
	{
		if (is_prefix_bin(cmd))
			return command;
		else
			command = ft_strjoin("/bin/", cmd);
	}
	return (command);
}


void clearArgIndexContainer (int argLocation[]);

int main(int ac, char **av, char **env) {
	/* variables for command parsing and storage*/
	char n, *parser, buf[80], *argv[20];
	int m, status, inword, continu;

	/* variables and flags for redirection (note: C does not have type bool; using integer value 0 or 1) */
	char *in_path, *out_path;
	int inputRedirectFlag, outputRedirectFlag;

	/* variables for piping */

	pid_t pid;

	/* left and right pipes */
	int l_pipe[2], r_pipe[2];

	/* container for recording argument locations in argv[] */
	int argLocation[20] = { 0 };

	while (1) {

		/* reset parsing and piping variable values */
		m = inword = continu  = pid = 0;

		/* begin parsing at beginning of buffer */
		parser = buf;

		/* reset redirection flags */
		inputRedirectFlag = outputRedirectFlag = 0;
		printf("shhh> ");
		while ((n = getchar()) != '\n' || continu)
		{
			if (n == ' ') {
				if (inword)
				{
					inword = 0;
					*parser++ = 0;
				}
			}
			else if (n == '\n')
				continu = 0;
			else if (n == '\\' && !inword)
				continu = 1;
			else {
				if (!inword)
				{
					inword = 1;
					argv[m++] = parser;
					*parser++ = n;
				}
				else
					*parser++ = n;
			}
		} /* end of command parsing */
		*parser++ = 0;

		argv[m] = 0;//зануление последенего аргумента

		//выход
		if (strcmp(argv[0], "exit") == 0)
			exit(0);

		int count = 0;
		/*
		 * manage redirection
		 * если нашли pipe то выставляем флаг и зануляем в массиве
		 * */
		int pipes = 0;
		while (argv[count] != 0) {
			if (strcmp(argv[count], "|") == 0) {
				argv[count] = 0;
				argLocation[pipes + 1] = count + 1;
				++pipes;
			}
			else if (strcmp(argv[count], "<") == 0) {
				in_path = strdup(argv[count + 1]);
				argv[count] = 0;
				inputRedirectFlag = 1;
			}
			else if (strcmp(argv[count], ">") == 0) {
				out_path = strdup(argv[count + 1]);
				argv[count] = 0;
				outputRedirectFlag = 1;
			}
			else {
				argLocation[count] = count;
			}
			++count;
		}
		/* end of redirection management */

		/* execute commands [<= in for-loop; n pipes require n+1 processes] */
		for (int index = 0; index <= pipes; ++index)
		{
			if (pipes > 0 && index != pipes)
			{
				/* if user has entered multiple commands with '|' */
				if (pipe(r_pipe) < 0)
					perror("pipe() error");
				/* no pipe(l_pipe); r_pipe becomes next child's l_pipe */
			}
			if ((pid = fork()) < 0)
				perror("fork() error");
			if (pid == 0)
			{
				if ((index == 0) && (inputRedirectFlag == 1))
				{
					int inputFileDescriptor = open(in_path, O_RDONLY, 0400);
					if (inputFileDescriptor == -1)
					{
						perror("input file failed to open\n");
						return (EXIT_FAILURE);
					}
					close(READ);
					dup(inputFileDescriptor);
					close(inputFileDescriptor);
				}
				/* end of input redirection management */

				if ((index == pipes) && (outputRedirectFlag == 1))
				{
					//printf("DEBUG: here we should be about to create our output file\n");
					int outputFileDescriptor = creat(out_path, 0700);
					if (outputFileDescriptor < 0)
					{
						perror("output file failed to open\n");
						return (EXIT_FAILURE);
					}
					close(WRITE);
					dup(outputFileDescriptor);
					close(outputFileDescriptor);
				}
				/* end of output redirection management */

				if (pipes > 0)
				{
					if (index == 0)
					{
						close(WRITE);
						dup(r_pipe[WRITE]);
						close(r_pipe[WRITE]);
						close(r_pipe[READ]);
					}
					else if (index < pipes)
					{
						close(READ);
						dup(l_pipe[READ]);
						close(l_pipe[READ]);
						close(l_pipe[WRITE]);
						close(WRITE);
						dup(r_pipe[WRITE]);
						close(r_pipe[READ]);
						close(r_pipe[WRITE]);
					} else
					{
						close(READ);
						dup(l_pipe[READ]);
						close(l_pipe[READ]);
						close(l_pipe[WRITE]);
					}
				}

				/* execute command */
//				execvp(argv[argLocation[index]], &argv[argLocation[index]]);
				char *command = check_bin_func(argv[argLocation[index]]);
				execve(command, &argv[argLocation[index]], env);
				free(command);
				/* if execvp() fails */
				perror("execution of command failed\n");
			}
			else
			{
				if (index > 0) {
					close(l_pipe[READ]);
					close(l_pipe[WRITE]);
				}
				l_pipe[READ] = r_pipe[READ];
				l_pipe[WRITE] = r_pipe[WRITE];
				/* parent waits for child process to complete */
				wait(&status);

			}
		}
		for (int i = 0; i < 20; ++i) {
			argv[i] = 0;
		}
	}
}

void clearArgIndexContainer (int argLocation[]){
	// clear argument container
	for (int i = 0; i < 20; ++i) {
		argLocation[i] = 0;
	}
}

//int pipes_func(int value, int pipes)
//{
//	int fd[2];
//	if (pipe(fd) < 0)
//		perror("pipe error");
//
//	pid_t pid;
//
//	if (pipes == 0)
//		return value;
//	if (pipe(fd) < 0)
//		return 1;
//	if ((pid = fork()) < 0)
//		return 1;
//	if (pid == 0)
//	{
//		int x;
//		read(fd[0], &x, sizeof(int));
//		x *= 2;
//		close(fd[0]);
//		write(fd[1], &x, sizeof(int));
//		close(fd[1]);
//	}
//	else
//	{
//		int x = value;
////		printf("enter a number: ");
////		scanf("%d", &x);
//
////		write(fd[1], &x, sizeof(int));
//		close(fd[1]);
//		wait(&pid);
//		read(fd[0], &x, sizeof(int));
//		printf("x = %d\n", x);
//		close(fd[0]);
//		pipes_func(x, pipes - 1);
//
//	}
//	write(1, &value, sizeof(int));
////	return x;
//}
//
//
//int main(int ac, char **av, char **env)
//{
//	int value = 5;
//
//	pipes_func(value, 3);
//
//	printf("value = %d\n", value);
//}
