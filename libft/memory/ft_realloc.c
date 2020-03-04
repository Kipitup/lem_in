/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 15:20:45 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloc(void **content, size_t new_size , size_t old_size)
{
	void	**tmp;

	tmp = NULL;
	if (content != NULL)
	{
		if (new_size > 0)
		{
			tmp = ft_memalloc(new_size);
			if (tmp != NULL)
			{
				ft_memcpy(tmp, content, old_size);
				if (tmp == NULL)
					ft_print_err_failure("tmp is NULL after cpy", STD_ERR);
				ft_memdel(content);
			}
		}
	}
	else
		ft_print_err_failure("realloc failed / content is NULL", STD_ERR);
	return (tmp);
}
