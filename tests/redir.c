
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*!
** n>
** перенаправляет вывод из файлового дескриптора n в файл. Вы должны иметь права на запись в файл.
** Если файла не существует, то он будет создан.
** Если файл существует, то все его содержимое, как правило, уничтожается без каких-либо предупреждений.
*/

/*!
** 	n>>
**также перенаправляет вывод из файлового дескриптора n в файл. Вы также должны иметь права на запись в файл.
** Если файла не существует, то он будет создан. Если файл существует, то вывод добавляется к его содержимому.
*/

int redir(char **file1, char **file2, char *redir)
{
	if ()
}

int main()
{
	pid_t pid;
	int status = 0;
	int newfd;
	if ((pid = fork()) < 0)
		exit(0);
	if (pid == 0)
	{

		int file =open("test.txt", O_CREAT | O_RDWR, 0777);
		if (file == -1)
		{
			printf("file not opened!!!\n");
			exit(file);
		}
		close(1);
		dup(newfd);
		close(newfd);
		exit(status);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status)!= 0)
		{
			if (WEXITSTATUS(status)!= 0)
			{
				printf("status = %d\n", WEXITSTATUS(status));
				exit(status);
			}
		}
	}

}
