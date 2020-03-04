/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 18:16:54 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "darray.h"

void	**ft_realloc(t_darray *array, size_t new_size, size_t old_size)
{
	void	**tmp;

	tmp = NULL;
	if (array != NULL)
	{
		if (new_size > 0)
		{
			tmp = ft_memalloc(new_size);
			if (tmp != NULL)
			{
				new_size > old_size ? ft_memcpy(tmp, array->contents, old_size)
					: ft_memcpy(tmp, array->contents, new_size);
				if (tmp == NULL)
					ft_print_err_failure("tmp is NULL after cpy", STD_ERR);
				darray_clear(&array);
			}
		}
	}
	else
		ft_print_err_failure("realloc failed / array is NULL", STD_ERR);
	return (tmp);
}
