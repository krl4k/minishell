/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:04:42 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/02 13:29:07 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list *temp;

	temp = lst;
	if (del)
	{
		if (temp)
		{
			(*del)(lst->content);
			temp->next = lst->next;
			free(lst);
		}
	}
}
