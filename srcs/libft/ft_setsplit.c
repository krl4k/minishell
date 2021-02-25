/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:22:39 by mwinter           #+#    #+#             */
/*   Updated: 2021/02/19 15:20:11 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_wordcount(char const *s, char *set)
{
	size_t res;

	res = 0;
	while (*s)
	{
		if (!ft_strchr(set, *s))
			res++;
		while (!ft_strchr(set, *s) && *(s + 1))
			s++;
		s++;
	}
	return (res);
}

static size_t	ft_strlen_sp(char const *s, char *set)
{
	size_t len;

	len = 0;
	while (!ft_strchr(set, *s) && *s)
	{
		s++;
		len++;
	}
	return (len);
}

void			ft_free_split(char **res)
{
	int i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		free(res[i]);
		res[i++] = NULL;
	}
	if (res)
	{
		free(res);
		res = NULL;
	}
}

void			ft_free_split_count(char **res, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (res[i])
			free(res[i]);
		i++;
	}
	free(res);
}

char			**ft_setsplit(const char *s, char *set)
{
	char	**res;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	if (!(res = (char **)malloc((ft_wordcount(s, set) + 1) * sizeof(char *))))
		return (NULL);
	while (i < ft_wordcount(s, set))
	{
		if (!(res[i] = (char *)malloc((ft_strlen_sp(&s[k], set)
			+ 1) * sizeof(char))))
			ft_free_split(res);
		while (ft_strchr(set, s[k]))
			k++;
		ft_strlcpy(res[i], &s[k], ft_strlen_sp(&s[k], set) + 1);
		while (!ft_strchr(set, s[k]) && s[k])
			k++;
		i++;
	}
	res[i] = NULL;
	return (res);
}
