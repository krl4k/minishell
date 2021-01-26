/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:39:31 by fgrisell          #+#    #+#             */
/*   Updated: 2021/01/26 12:54:46 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_all(t_all *all)
{
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		perror(MALLOC_ERROR);
	all->flag = FLAG_NONE;
}
