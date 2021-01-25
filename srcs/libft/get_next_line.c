/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 10:31:52 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/14 14:45:09 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_eof(char **remainder, char **line)
{
	if (ft_strchr(*remainder, '\0'))
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
	return (0);
}

static int	ft_error(ssize_t ret, char **remainder)
{
	if (ret < 0)
	{
		if (*remainder)
		{
			free(*remainder);
			*remainder = NULL;
		}
		return (-1);
	}
	return (0);
}

static int	ft_check_result(int ret, char **remainder, char **line)
{
	char *tmp;
	char *new_line_ptr;

	if (!ret && !*remainder)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ft_error(ret, &*remainder))
		return (-1);
	if ((new_line_ptr = ft_strchr(*remainder, '\n')))
	{
		*new_line_ptr = '\0';
		*line = ft_strdup(*remainder);
		tmp = ft_strdup(++new_line_ptr);
		if (!tmp || !*line)
			return (-1);
		free(*remainder);
		*remainder = tmp;
		return (1);
	}
	return (ft_check_eof(&*remainder, &*line));
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder[1024];
	char		*buff;
	char		*tmp;
	int			ret;

	if (!line || fd < 0 || fd > 1024 || BUFFER_SIZE < 1 ||
		!(buff = (char *)malloc(BUFFER_SIZE + 1)) || (read(fd, buff, 0) < 0))
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!remainder[fd])
			remainder[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(remainder[fd], buff);
			free(remainder[fd]);
			remainder[fd] = tmp;
		}
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	buff = NULL;
	return (ft_check_result(ret, &remainder[fd], &*line));
}
