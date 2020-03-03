/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:59:36 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 20:04:06 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	*darray_pop(t_darray *array)
{
	void	*element;

	element = NULL;
	if (array->end >= 0)
	{
		element = darray_remove(array, array->end);
		if (element != NULL)
		{
			if (array->end > 0)
				array->end--;
			if ((array->end > array->expand_rate) && (array->end % array->expand_rate))
				darray_contract(array);
		}
	}
	else
		ft_print_err_null(FAILED_TO_POP, STD_ERR);
	return (element);
}
