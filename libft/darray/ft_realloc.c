/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 16:11:05 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "darray.h"

static void	darray_destroy_content(t_darray **array)
{
	if (array != NULL && *array != NULL)
	{
		if ((*array)->contents != NULL)
		{
			free((*array)->contents);
			(*array)->contents = NULL;
		}
	}
}

void		**ft_realloc(t_darray *array, size_t new_size, size_t old_size)
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
