/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:05:40 by fgrisell          #+#    #+#             */
/*   Updated: 2020/10/31 14:05:12 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *s)
{
	char		*res;
	size_t		size;
	char		*tmp;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	if (!(res = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	tmp = res;
	while (size--)
		*tmp++ = *s++;
	return (res);
}
