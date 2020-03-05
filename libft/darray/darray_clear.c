/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:35:38 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 11:05:44 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	darray_clear(t_darray **array)
{
	size_t 		i;
	t_darray	*to_del;

	i = 0;
	if (array != NULL && *array != NULL)
	{
		to_del = *array;
		if (to_del->sizeof_elem > 0)
		{
			while (i <= to_del->end)
			{
				if (to_del->contents[i] != NULL)
					to_del->del_func((to_del->contents) + i);
				i++;
			}
		}
	}
	else
		ft_perror_void(CLEAR_NULL, STD_ERR);
}
