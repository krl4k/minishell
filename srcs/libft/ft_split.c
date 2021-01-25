/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:14:01 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/03 18:11:35 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cntwrd(char const *s, char c)
{
	int		i;
	int		cntwrd;

	cntwrd = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			cntwrd++;
		i++;
	}
	return (cntwrd);
}

static int		len_wrd(char const *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

static void		*ft_free(char **split, int cur_wrd)
{
	int i;

	i = 0;
	while (i < cur_wrd)
	{
		free(split[i]);
		i++;
	}
	return (NULL);
}

static char		**splitting(char const *s, char **split, char c, int cnt_wrd)
{
	int i;
	int j;
	int len;

	i = 0;
	while (i < cnt_wrd)
	{
		while (*s == c)
			s++;
		len = len_wrd(s, c);
		if (!(split[i] = (char *)malloc((len + 1) * sizeof(char))))
			return (ft_free(split, i));
		j = 0;
		while (j < len)
		{
			split[i][j++] = *s++;
		}
		split[i][j] = '\0';
		i++;
	}
	split[i] = NULL;
	return (split);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	size_t	cnt_wrd;

	if (!s)
		return (NULL);
	cnt_wrd = ft_cntwrd(s, c);
	if (!(split = (char **)malloc((cnt_wrd + 1) * sizeof(char *))))
		return (NULL);
	return (splitting(s, split, c, cnt_wrd));
}
