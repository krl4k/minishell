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
	char *line;
	while (1)
	{
		get_next_line(0, &line);

		pid_t pid = fork();
		if (pid < 0)
			perror("fork()\n");
		if (pid == 0)
		{
			printf("CHILD:\n");
			status = execve(line,argv,env);
			exit(status);
		}
		else
		{
			wait(&status);
			printf("Выполнено успешно!\n");
		}
	}
	/*
	if(argc == 1)  *//* есть ли еще аргументы *//*
	{
		printf("%s запускает сама себя опять...\n",argv[0]);
		execve("/bin/ls",argv,env);
		printf("сюда мы не попадем!!!\n");
		perror("EXEC:");
	}
	if (argc == 0)
	{
		printf("Вызван %s\n",argv[0]);
		execve("/bin/c_pwd",argv,env);
	}*/



//	printf("%s вызвана с аргументами:\n",argv[0]);
//	for(loop = 1;loop<=argc;loop++)
//		puts(argv[loop]);
	return 0;
}