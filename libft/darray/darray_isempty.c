/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_isempty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 10:20:01 by francis           #+#    #+#             */
/*   Updated: 2020/05/23 10:26:51 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

int8_t	darray_isempty(t_darray *array)
{
	size_t	i;
	int8_t	ret;

	i = 0;
	ret = SUCCESS;
	if (array != NULL)
	{
		while (i <= array->end)
		{
			if (array->contents[i] != NULL)
				ret = FAILURE;
			i++;
		}
	}
	return (ret);
}
