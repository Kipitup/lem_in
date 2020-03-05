/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:41:29 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 11:31:09 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

int8_t	darray_push(t_darray *array, void *element)
{
	int8_t	ret;

	ret = SUCCESS;
	if (array != NULL)
	{
		if ((array->end + 1) >= array->max)
			ret = darray_expand(array);
		array->end++;
		if (ret == SUCCESS)
			array->contents[array->end] = element;
	}
	else
		ret = ft_print_err_failure(ARRAY_IS_NULL, STD_ERR);
	return (ret);
}
