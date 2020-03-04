/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 09:49:47 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *content, size_t size)
{
	void	*tmp;

	tmp = NULL;
	if (content != NULL)
	{
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
	}
	else
		ft_print_err_null("realloc failed / content is NULL", STD_ERR);
	return (tmp);
}
