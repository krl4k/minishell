/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrisell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:21:14 by fgrisell          #+#    #+#             */
/*   Updated: 2020/11/02 13:39:14 by fgrisell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int num;
	int m;
	int i;

	i = 0;
	m = 1;
	num = 0;
	while (str[i] == ' ' || str[i] < 27)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (num * 10 < num)
			return ((m < 0) ? 0 : -1);
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * m);
}
