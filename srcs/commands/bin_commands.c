/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:54:52 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/27 10:54:53 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** checks the /bin/ prefix
** \author fgrisell
*/

static int	is_prefix_bin(char *line)
{
	if (ft_strncmp("/bin/", line, 5) == 0)
		return (1);
	return (0);
}

char		*check_bin_func(char *cmd)
{
	char		*command;
	int			i;
	int			flag;
	char		*temp;
	static char	*bin_array[] = {"cp", "df", "hostname", "link", "mv", "rm",
	"stty", "test", "bash", "csh", "echo", "kill", "ln", "pax", "rmdir", "sync",
	"unlink", "cat", "date", "ed", "ksh", "ls", "ps", "sh", "syslog.py", "zsh",
	"wait4path", "chmod", "dd", "expr", "launchctl", "mkdir", "tcsh", "sleep",
	"pwd", NULL};

	flag = 0;
	i = -1;
	command = ft_strdup(cmd);
	while (bin_array[++i])
	{
		if (ft_strcmp(cmd, bin_array[i]) == 0)
			flag = 1;
	}
	if (flag)
	{
		if (is_prefix_bin(cmd))
			return (command);
		else
		{
			free(command);
			command = ft_strjoin("/bin/", cmd);
		}
	}
	return (command);
}