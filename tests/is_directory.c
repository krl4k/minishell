# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

int main()
{
	char *cmd = strdup("/Users/fgrisell");

	int fd;
	if ((fd = open(cmd, O_RDONLY)) < 0)
		perror(cmd);
}