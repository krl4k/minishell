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

int     word_count(char *line)
{
    int i;
    int cnt_q;

    i = 0;
    cnt_q = 0;
    while (*line)
    {
        if (*line == '\"')
        {
            cnt_q++;
            *line++;
            while (*line != '\"')
                line++;
            if (*line == '\"')
            {
                line++;
                cnt_q++;
            }

        }
    }
}

char    *split_q(char *line)
{
    char **res;

    if (!line)
        return (NULL);
    if (!(res = (char **)malloc(sizeof(char *) * (word_count(line) + 1))))
        return (NULL);
}
