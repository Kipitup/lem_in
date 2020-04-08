/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:47:17 by fkante            #+#    #+#             */
/*   Updated: 2020/04/08 16:17:46 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if ((char*)dst > (const char*)src)
	{
		while (len-- > i)
			((char*)dst)[len] = ((const char*)src)[len];
	}
	else
	{
		while (i < len)
		{
			((char*)dst)[i] = ((const char*)src)[i];
			i++;
		}
	}
	return (dst);
}
