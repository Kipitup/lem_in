/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:49:20 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 11:05:43 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	darray_destroy_content(t_darray **array)
{
	if (array != NULL && *array != NULL)
	{
		if ((*array)->contents != NULL)
		{
			free((*array)->contents);
			(*array)->contents = NULL;
		}
	}
}

void	darray_destroy(t_darray **array)
{
	if (array != NULL && *array != NULL)
	{
		if ((*array)->contents != NULL)
		{
			free((*array)->contents);
			(*array)->contents = NULL;
		}
		ft_memdel((void**)array);
	}
}

void	darray_clear_destroy(t_darray **array)
{
	darray_clear(array);
	darray_destroy(array);
}
