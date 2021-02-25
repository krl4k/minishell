/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 12:29:52 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/07 17:40:43 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *mem;

	if (!(mem = (char *)malloc(count * size)))
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
