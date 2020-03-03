/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 13:02:22 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *content, size_t size)
{
	void	*tmp;
	
	if (size > 0)
	{
		tmp = ft_memalloc(size);
		if (tmp != NULL)
		{
			ft_memcpy(tmp, content, size);
			ft_memdel(&content);
			return (tmp);
		}
	}
	return (NULL);
}
