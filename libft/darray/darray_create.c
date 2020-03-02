/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:04:30 by fkante            #+#    #+#             */
/*   Updated: 2020/03/02 14:42:25 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"

t_darray	*darray_create(size_t element_size, size_t initial_max)
{
	t_array	*array;
	ssize_t	ret;

	ret = FAILURE;
	array = ft_memalloc(sizeof(t_array));
	if (initial_max == 0)
	{
		ft_print_err_void(INITIAL_MAX_ZERO, STD_ERR);
		return (NULL);
	}
	if (array != NULL)
	{
		array->max = initial_max;
		array->contents = ft_memalloc(sizeof(void *)*initial_max);
		if (array->contents == NULL)
			return (NULL);
		array->end = 0;
		array->element_size = element_size;
		array->expand_rate = DEFAULT_EXPAND_RATE;
	}
	return (array);
}
