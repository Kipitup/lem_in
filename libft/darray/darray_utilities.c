/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:36:23 by fkante            #+#    #+#             */
/*   Updated: 2020/03/02 14:03:06 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"

static inline void	darray_set(t_darray *array, int32_t i, void *el)
{
	if (i < array->max)
	{
		if (i > array->end)
			array->end = i;
		array->contents[i] = el;
	}
	else
		ft_print_err_void(SET_ABOVE_MAX, STD_ERR);
}

static inline void	*darray_get(t_darray *array, int i)
{
	if (i < array->max)
		return (array->contents[i]);
	else
	{
		ft_print_err_void(GET_ABOVE_MAX, STD_ERR);
		return (NULL);
	}
}

static inline void	*darray_remove(t_darray *array, int i)
{
	void	*el;

	el = array->contents[i];
	array->contents[i] = NULL;
	return (el);
}

static inline void	*darray_new(t_darray *array)
{
	if (array->selement_size > 0)
		return (ft_memalloc(array->element_size));
	else
		ft_print_err_void(ARRAY_SIZE_ZERO, STD_ERR);
}
