/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_modify_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:59:46 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 18:53:42 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

static int8_t	darray_resize(t_darray *array, size_t newsize)
{
	void	**new_content;
	size_t	old_max;
	int8_t	ret;

	ret = FAILURE;
	if (array == NULL)
		ret = ft_print_err_failure(ARRAY_IS_NULL, STD_ERR);
	else if (newsize == 0)
		ret = ft_print_err_failure(NEWSIZE_ZERO, STD_ERR);
	else
	{
		old_max = array->max;
		array->max = newsize;
		new_content = ft_realloc(array, (array->max * sizeof(void*)), (old_max * sizeof(void*)));
		if (new_content != NULL)
		{
			array->contents = new_content;
			ret = SUCCESS;
		}
		else
			ft_print_err_failure(FAILED_TO_EXPAND, STD_ERR);
	}
	return (ret);
}

/*
** Since array->max is an index
*/

int8_t			darray_expand(t_darray *array)
{
	size_t	old_max;
	int8_t	ret;

	ret = FAILURE;
	if (array != NULL)
	{
		old_max = array->max;
		ret = darray_resize(array, array->max + array->expand_rate);
		if (ret == SUCCESS)
			ft_memset(array->contents + old_max, 0, array->expand_rate);
	}
	else
		ft_print_err_void(ARRAY_IS_NULL, STD_ERR);
	return (ret);
}

int8_t			darray_contract(t_darray *array)
{
	size_t newsize;

	if (array != NULL)
	{
		newsize = (array->end < array->expand_rate) ? array->expand_rate
			: array->end;
		return (darray_resize(array, newsize));
	}
	else
		return (ft_print_err_failure(ARRAY_IS_NULL, STD_ERR));
}
