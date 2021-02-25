/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:21:08 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/02 13:16:49 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *new_head;

	if (new)
	{
		new_head = new;
		if ((!(*lst)))
			*lst = new_head;
		else
		{
			new_head->next = *lst;
			*lst = new_head;
		}
	}
}
