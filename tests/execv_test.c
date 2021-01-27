#include <stdio.h>
#include <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include "../srcs/libft/libft.h"

int main(int argc,char *argv[], char **env)
{

	printf("%s работает...\n",argv[0]);

	int status;
	char **commands = (char **)malloc(3 * sizeof(char *));
	commands[0] = ft_strdup("/bin/ls");
	commands[1] = ft_strdup("-");
	commands[2] = NULL;
	int num_cmd = 0;
	while (1)
	{
//		get_next_line(0, &);
		printf("выберете флаг : \n");
		printf("1 = -l\n");
		printf("2 = -la\n");
		printf("3 = invalid\n\n");

		printf("protm: ");

		scanf("%d", &num_cmd);
		if (num_cmd==1)
			commands[1] = ft_strdup("-l");
		else if (num_cmd==2)
			commands[1] = ft_strdup("-la");
		else if (num_cmd == 3)
			commands[1] = ft_strdup("invalid");
		else
			commands[1] = NULL;

		pid_t pid = fork();
		if (pid < 0)
			perror("fork()\n");
		if (pid == 0)
		{
			printf("CHILD:\n");
			status = execve(commands[0],commands,env);
			exit(status);
		}
		else
		{
			wait(&status);
//			waitpid(pid, &status, 0);
			if (WIFEXITED(status) != 0)
			{
				printf("status = %d\n", WEXITSTATUS(status));
//				break;
			}
			else
				break;
		}
		if (WIFEXITED(status) != 0)
			printf("Выполнено успешно!\n\n");
		else
			printf("не выполнено!\n\n");


	}
	return 0;
}