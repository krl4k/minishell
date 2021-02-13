/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <mwinter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 17:59:06 by mwinter           #+#    #+#             */
/*   Updated: 2021/01/26 13:39:09 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t p_size, size_t n_size)
{
	void *new;

	if (!p)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * n_size)))
	{
		free(p);
		return (NULL);
	}
	ft_memcpy(new, p, p_size < n_size ? p_size : n_size);
	free(p);
	return (new);
}
