/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:54:19 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/01 14:19:36 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trim_start(char const *s, char const *set)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s[i])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_trim_end(char const *s, char const *set)
{
	size_t i;
	size_t j;

	i = ft_strlen(s) - 1;
	j = 0;
	while (i > 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s[i])
				break ;
			j++;
		}
		if (j == ft_strlen(set))
			return (i + 1);
		i--;
	}
	return (i + 1);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trim;

	if (!s1)
		return (ft_strdup(""));
	i = 0;
	start = ft_trim_start(s1, set);
	end = ft_trim_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	if (!(trim = (char *)malloc((end - start + 1) * sizeof(char))))
		return (NULL);
	while (start < end)
	{
		trim[i] = s1[start];
		start++;
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
