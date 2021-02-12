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

static int	is_prefix_bin(char **path, char *line)
{
	int i;

	i = 0;
	while (*line && *line == '/')
		line++;
	line--;
	while (path[i])
	{
		if (ft_strncmp(path[i], line, ft_strlen(path[i])) == 0)
		{
			if (line[ft_strlen(path[i])])
			{
				if (line[ft_strlen(path[i])] == '/')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

char		*check_cmd(t_all *all, char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*temp_cmd;
	int		fd;

	i = 0;
	if (is_prefix_bin(all->old_path, cmd))
		return (ft_strdup(cmd));
	temp_cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
		if ((temp = ft_strjoin(path[i], temp_cmd)))
		{
			if ((fd = open(temp, O_RDONLY)) > 0)
			{
				close(fd);
				free(temp_cmd);
				return (temp);
			}
			free(temp);
		}
		i++;
	}
	free(temp_cmd);
	return (ft_strdup(cmd));
}

/*
** if 	PATH not exist
** else PATH 	 exist
*/

char		*get_path(t_all *all, char *cmd)
{
	char	**path;
	char	*command;
	int		i;

	i = 0;
	while (i < all->env_array->current_size)
	{
		if (ft_strcmp("PATH", all->env_array->key[i]) == 0)
			break ;
		i++;
	}
	if (i == all->env_array->current_size)
		if (is_prefix_bin(all->old_path, cmd))
			return (ft_strdup(cmd));
		else
			return (ft_strdup(cmd));
	else
	{
		if (!(path = ft_split(all->env_array->value[i], ':')))
			return (NULL);
		command = check_cmd(all, path, cmd);
		ft_free_split(path);
	}
	return (command);
}

char		*check_bin_func(t_all *all, char *cmd)
{
	char *command;

	command = get_path(all, cmd);
	return (command);
}
