/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:11:30 by fkante            #+#    #+#             */
/*   Updated: 2019/04/26 15:35:09 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buff, int c, size_t len)
{
	if (len == 0)
		return (buff);
	while (--len)
		((unsigned char*)buff)[len] = (unsigned char)c;
	((unsigned char*)buff)[len] = (unsigned char)c;
	return (buff);
}
