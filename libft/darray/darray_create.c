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

t_darray	*darray_create(size_t element_size, size_t init_max)
{
	t_array	*array;

	array = NULL;
	if (init_max != 0)
	{
		ft_print_err_void(INITIAL_MAX_ZERO, STD_ERR);
		array = ft_memalloc(sizeof(t_array));
		if (array != NULL)
		{
			array->max = init_max;
			array->contents = ft_memalloc(init_max * sizeof(void *));
			if (array->contents == NULL)
				return (NULL);
			array->end = 0;
			array->element_size = element_size;
			array->expand_rate = DEFAULT_EXPAND_RATE;
		}
	}
	return (array);
}
