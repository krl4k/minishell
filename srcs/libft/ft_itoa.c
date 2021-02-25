/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:44:51 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/01 16:15:01 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_num_str(int n)
{
	int size;

	size = 0;
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char	*num_str;
	int		temp;
	size_t	len_num_str;

	len_num_str = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((temp = n) < 0)
		n = -n;
	len_num_str = (temp > 0) ? ft_len_num_str(n) : ft_len_num_str(n) + 1;
	if (!(num_str = (char *)malloc((len_num_str + 1) * sizeof(char))))
		return (NULL);
	num_str[len_num_str] = '\0';
	while (n || len_num_str)
	{
		num_str[len_num_str - 1] = n % 10 + 48;
		--len_num_str;
		n /= 10;
	}
	if (temp < 0)
		num_str[0] = '-';
	return (num_str);
}
