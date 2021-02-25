/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:40:17 by fgrisell          #+#    #+#             */
/*   Updated: 2020/10/30 20:52:36 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** the first character that does not match
** has a lower value in str1 than in str2
** the contents of both strings are equal
** the first character that does not match has
** a greater value in str1 than in str2
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
