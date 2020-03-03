/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:36:23 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 19:58:38 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

static void	*darray_set_bis(t_darray *array, size_t i, void *element)
{
	void	*tmp;

	tmp = NULL;
	if (array != NULL)
	{
		if (i < array->max)
		{
			if (i > array->end)
				array->end = i;
			array->contents[i] = element;
			tmp = array->contents[i];
			return (tmp);
		}
		else
			return(ft_print_err_null(SET_ABOVE_MAX, STD_ERR));
	}
	else
		return (ft_print_err_null(ARRAY_IS_NULL, STD_ERR));
}

void	darray_set(t_darray *array, size_t i, void *element)
{
	if (array != NULL)
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
	else
		return (ft_print_err_void(ARRAY_IS_NULL, STD_ERR));
}

void	*darray_get(t_darray *array, size_t i)
{
	if (array != NULL)
	{
		if (i < array->max)
			return (array->contents[i]);
		else
			return (ft_print_err_null(GET_ABOVE_MAX, STD_ERR));
	}
	else
		return (ft_print_err_null(ARRAY_IS_NULL, STD_ERR));

}

void	*darray_remove(t_darray *array, size_t index)
{
	void	*element;

	element = NULL;
	if (array != NULL)
	{
		element = array->contents[index];
		array->contents[index] = NULL;
	}
	else
		ft_print_err_void(ARRAY_IS_NULL, STD_ERR);
	return (element);
}

void	*darray_new_and_set(t_darray *array, size_t index, void *element)
{
	void	*tmp;

	if (array != NULL)
	{
		if (array->element_size > 0)
		{
			tmp = ft_memalloc(array->element_size);
			if (tmp == NULL)
					return (ft_print_err_null(CONTENT_FAIL, STD_ERR));
			tmp = darray_set_bis(array, index, element);
			return (tmp);
		}
		else
			return (ft_print_err_null(ARRAY_SIZE_ZERO, STD_ERR));
	}
	return (ft_print_err_null(ARRAY_IS_NULL, STD_ERR));
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
