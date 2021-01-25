/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:17:17 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/02 13:27:46 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list *temp;
	t_list *next;

	temp = *head;
	if (del)
	{
		if (temp)
		{
			while (temp)
			{
				next = temp->next;
				(*del)(temp->content);
				free(temp);
				temp = next;
			}
			*head = NULL;
		}
	}
}
