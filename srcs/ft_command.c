/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  ft_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 13:42:07 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_strchrset(char *line, char *set)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (ft_strchr(set, line[i]))
            return (&line[i]);
        i++;
    }
    return (NULL);
}

char *ft_command(char *cmd_line)
{
    char *p;
    char *tmp;
    char **cmd;

    if (!(p = ft_strchr(cmd_line, ' ')))
    {
        tmp = cmd_line;
        p = '\0';
        cmd[0] = ft_strjoin("", tmp);
        free(tmp);
        return (NULL);
    }
	return (NULL);
}