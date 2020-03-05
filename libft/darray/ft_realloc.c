/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 11:37:43 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "darray.h"

void	**ft_realloc(t_darray *array, size_t new_size, size_t old_size)
{
	void	**tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (array != NULL)
	{
		new_size = (new_size > old_size) ? new_size : old_size;
		if (new_size > 0)
		{
			tmp = ft_memalloc(new_size * sizeof(void*));
			if (tmp != NULL)
			{
				while (i <= array->end)
				{
					tmp[i] = array->contents[i];
					i++;
				}
				darray_destroy_content(&array);
			}
		}
	}
	else
		ft_perror_failure("realloc failed / array is NULL", STD_ERR);
	return (tmp);
}
