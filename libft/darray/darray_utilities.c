/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 13:36:23 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 13:43:00 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

int8_t	darray_set(t_darray *array, size_t i, void *element)
{
	int8_t	ret;

	ret = FAILURE;
	if (array != NULL)
	{
		if (i < array->max)
		{
			if (i > array->end)
				array->end = i;
			array->contents[i] = element;
			ret = SUCCESS;
		}
		else
			ft_print_err_failure(SET_ABOVE_MAX, STD_ERR);
	}
	else
		ft_print_err_failure(NULL_OR_WRONG_ELEM, STD_ERR);
	return (ret);
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

int8_t	darray_new_and_set(t_darray *array, size_t index, void *element)
{
	int8_t	ret;

	ret = FAILURE;
	if (array != NULL)
	{
		if (array->element_size > 0)
		{
			array->contents[index] = ft_memalloc(array->element_size);
			if (array->contents[index] != NULL)
				ret = darray_set(array, index, element);
			else
				ft_print_err_failure(CONTENT_FAIL, STD_ERR);
		}
		else
			ft_print_err_failure(ARRAY_SIZE_ZERO, STD_ERR);
	}
	else
		ft_print_err_failure(ARRAY_IS_NULL, STD_ERR);
	return (ret);
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
