/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:39:09 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_n(char *flag)
{
    int i;

    i = 1;
    while (flag[i])
    {
        if (flag[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

void    ft_echo(char *cmd)
{
    int i;

    if (check_n(cmd[1]))
    {
        i = 1;
        while (cmd[i])
        {
            write(1, cmd[i], ft_strlen(cmd[i]));
            write(1, " ", 1);
            i++;
        }
        write(1, "\n", 1);
    }
    else
    {
        i = 1;
        while (cmd[i++])
            write(1, cmd[i], ft_strlen(cmd[i]));
    }
}

