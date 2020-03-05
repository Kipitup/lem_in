/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:04:30 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 11:05:42 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

t_darray	*darray_create(size_t sizeof_elem, size_t init_max,
							t_del_func del_func)
{
	t_darray	*array;

	array = NULL;
	if (init_max > 0)
	{
		array = ft_memalloc(sizeof(t_darray));
		if (array != NULL)
		{
			array->end = 0;
			array->max = init_max;
			array->element_size = sizeof_elem;
			array->expand_rate = DEFAULT_EXPAND_RATE;
			array->del_func = (del_func == NULL) ? &ft_memdel : del_func;
			array->contents = ft_memalloc(init_max * sizeof(void *));
			if (array->contents == NULL)
			{
				darray_destroy(&array);
				ft_print_err_null(CONTENT_FAIL, STD_ERR);
			}
		}
	}
	else
		ft_print_err_null(INITIAL_MAX_ZERO, STD_ERR);
	return (array);
}
