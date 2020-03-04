/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:04:30 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 14:45:25 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

t_darray	*darray_create(size_t element_size, size_t init_max)
{
	t_darray	*array;

	array = NULL;
	if (init_max != 0)
	{
		array = ft_memalloc(sizeof(t_darray));
		if (array != NULL)
		{
			array->max = init_max;
			array->contents = ft_memalloc(init_max * sizeof(void *));
			if (array->contents == NULL)
			{
				darray_destroy(&array);
				return (ft_print_err_null(CONTENT_FAIL, STD_ERR));
			}
			array->end = 0;
			array->element_size = element_size;
			array->expand_rate = DEFAULT_EXPAND_RATE;
		}
	}
	else
		ft_print_err_void(INITIAL_MAX_ZERO, STD_ERR);
	return (array);
}
