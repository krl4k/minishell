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

int check_quotes(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        if (*str == '\"')
            i++;
        str++;
    }
    return (i);
}

int check_flag(char *cmd, int *i)
{
    int k;

    k = *i;
    if (cmd[*i] != '-')
        return (0);
    (*i)++;
    while (cmd[*i] && cmd[*i] != ' ')
    {
        if (cmd[*i] != 'n')
        {
            *i = k;
            return (0);
        }
        (*i)++;
    }
    return (1);
}

void print_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        write(1, " ", 1);
        i++;
    }
}
void    ft_echo(char *cmd)
{
    int i;
    int flag;
    int quotes;
    char *tmp;
    char **args;

    i = 1;
    tmp = cmd;
    cmd = ft_strchr(cmd, ' ');
    while (IS_SPACE(cmd[i]))
        i++;
    flag = 0;
    while (cmd[i])
    {
        flag = check_flag(cmd, &i);
        if (!flag)
            break ;
        while (IS_SPACE(cmd[i]))
            i++;
        if (cmd[i] != '-')
            break;
    }
    quotes = 0;
    if (cmd[i] == '\"')
        quotes = check_quotes(&cmd[i]);
    if (quotes % 2 != 0 && quotes != 0)
    {
        write(2, "syntax error\n", 13);
        return ;
    }
    else if (quotes % 2 == 0)
        args = ft_setsplit(&cmd[i], "\"");
    else
        args = ft_setsplit(&cmd[i], " ");
    print_args(args);
    ft_free_split(args);
    if (!flag)
        write(1, "\n", 1);
    cmd = tmp;
}

