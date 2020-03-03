/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:35:38 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 15:50:39 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

void	darray_clear(t_darray **array)
{
	size_t i;

	i = 0;
	if ((*array)->element_size > 0)
	{
		while (i < (*array)->max)
		{
			if ((*array)->contents[i] != NULL)
				ft_memdel((*array)->contents + i);
			i++;
		}
	}
}
