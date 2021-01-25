/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:05:53 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/01 18:38:27 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join(char const *s2, size_t s2l, char *join, size_t i)
{
	size_t s1l;

	s1l = 0;
	while (s1l < s2l)
	{
		join[i] = s2[s1l];
		s1l++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1l;
	size_t		s2l;
	size_t		i;
	char		*join;

	if (!s1 || !s2)
		return (ft_strdup(""));
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	i = 0;
	if (!(join = (char *)malloc((s1l + s2l) * sizeof(char))))
		return (NULL);
	while (i < s1l)
	{
		join[i] = s1[i];
		i++;
	}
	s1l = 0;
	return (ft_join(s2, s2l, join, i));
}
