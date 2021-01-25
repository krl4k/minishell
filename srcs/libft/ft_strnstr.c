/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:15:47 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/03 12:06:19 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp(const char *hst, const char *ndl, size_t len)
{
	while (*ndl && len)
	{
		if (*hst != *ndl)
			return (0);
		hst++;
		ndl++;
		len--;
	}
	if (*ndl)
		return (0);
	return (1);
}

char		*ft_strnstr(const char *hst, const char *ndl, size_t len)
{
	char *ans;

	while (!*ndl || ndl == hst)
		return ((char *)hst);
	if (ft_strlen(hst) < ft_strlen(ndl))
		return (NULL);
	while (*hst && len)
	{
		if (*hst == *ndl)
		{
			ans = (char *)hst;
			if (ft_cmp(hst, ndl, len))
				return (ans);
		}
		hst++;
		len--;
	}
	return (NULL);
}
