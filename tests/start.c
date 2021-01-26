#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../srcs/libft/libft.h"

/*
  Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);

int lsh_help(char **args);

int lsh_exit(char **args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
		"cd",
		"",
		"help",
		"exit"
};

int (*builtin_func[])(char **) = {
		&lsh_cd,
		&lsh_help,
		&lsh_exit
};

int lsh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	} else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return 1;
}

int lsh_help(char **args)
{
	int i;
	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < lsh_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
}

int lsh_launch(char **args, char **env)
{
	pid_t pid, wpid;
	int status;

	if ((pid = fork()) < 0)
		perror("fork()\n");
	if (pid == 0)
	{
		printf("CHILD!\n");
		if (execvp(args[0], args))
		{
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_execute(char **args, char **env)
{
	int i;

	if (args[0] == NULL)
	{
		return 1;
	}

	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}

	return lsh_launch(args, env);
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

/*
**  loop for ever
**
*/
void lsh_loop(char **env)
{
	char *line;
	char **args;
	int status;

	status = 1;
	while (status)
	{
		status = 0;
		write(1, "> ", 3);
		get_next_line(0, &line);
		//args = lsh_split_line(line);
		status = lsh_execute(args, env);

		free(line);
		free(args);
	}
}

int main(int argc, char **argv, char **env)
{
	lsh_loop(env);

	return EXIT_SUCCESS;
}