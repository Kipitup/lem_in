/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:36:23 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 13:24:17 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	darray_set(t_darray *array, size_t i, void *element)
{
	if (i < array->max)
	{
		if (i > array->end)
			array->end = i;
		array->contents[i] = element;
	}
	else
		ft_print_err_void(SET_ABOVE_MAX, STD_ERR);
}

void	*darray_get(t_darray *array, size_t i)
{
	if (i < array->max)
		return (array->contents[i]);
	else
		return (ft_print_err_null(GET_ABOVE_MAX, STD_ERR));
}

void	*darray_remove(t_darray *array, size_t i)
{
	void	*element;

	element = array->contents[i];
	array->contents[i] = NULL;
	return (element);
}

void	*darray_new(t_darray *array)
{
	if (array != NULL)
	{
		if (array->element_size > 0)
			return (ft_memalloc(array->element_size));
		else
			return (ft_print_err_null(ARRAY_SIZE_ZERO, STD_ERR));
	}
	return (ft_print_err_null(ARRAY_IS_NULL, STD_ERR));
}
