/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <a.martino@sutdent.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:31:14 by amartino          #+#    #+#             */
/*   Updated: 2020/03/07 19:58:06 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

int8_t		hashmap_resize(t_hashmap *map)
{
	void		**content;
	size_t		new_size;
	size_t		i;
	int8_t		ret;

	ret = SUCCESS;
	i = 0;
	new_size = DEFAULT_NB_OF_BUCKETS * 3;
	ft_printf("new_size is %u\n", new_size);
	new_size = (size_t)ft_find_next_prime(new_size);
	ft_printf("new_size prime is %u\n", new_size);
	content = ft_memalloc(new_size * (sizeof(t_darray*)));
	if (content != NULL)
	{
		while (i < map->size)
		{
			if (map->bucket[i] != NULL)
			{
				
			}
			i++;
		}
	}
	else
		ret = ft_perror_failure(RESIZE_FAIL, STD_ERR);
	return (ret);
}
