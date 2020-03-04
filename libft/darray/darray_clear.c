/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:35:38 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 15:03:28 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	darray_clear(t_darray **array, t_del_func func)
{
	size_t i;

	i = 0;
	if (array != NULL && *array != NULL)
	{
		if ((*array)->element_size > 0)
		{
			while (i < (*array)->max)
			{
				if ((*array)->contents[i] != NULL)
					func(((*array)->contents) + i);
				i++;
			}
		}
	}
	else
		ft_print_err_void(CLEAR_NULL, STD_ERR);
}
