/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:51:27 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/02 13:20:02 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *temp;

	if (f)
	{
		if (lst)
		{
			temp = lst;
			while (temp)
			{
				(*f)(temp->content);
				temp = temp->next;
			}
		}
	}
}
