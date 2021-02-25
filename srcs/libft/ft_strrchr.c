/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:58:56 by fgrisell          #+#    #+#             */
/*   Updated: 2020/10/30 20:15:16 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t len;

	len = ft_strlen(s) + 1;
	if (!s)
		return (NULL);
	while (len > 0)
	{
		if (s[len - 1] == (unsigned char)c)
			return ((char *)s + len - 1);
		len--;
	}
	return (NULL);
}
