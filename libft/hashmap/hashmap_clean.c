/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:42:38 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 11:27:11 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "darray.h"

void	del_node(void **node)
{
	t_hashnode *node_tmp;

	if (node != NULL && *node != NULL)
	{
		node_tmp = *((t_hashnode**)node);
		ft_memdel(&(node_tmp->key));
		ft_memdel(&(node_tmp->data));
		ft_memdel(node);
	}
}

void	del_map(t_hashmap **map_to_del)
{
	t_hashmap *map;
	size_t		i;
	
	i = 0;
	if (map_to_del != NULL && *map_to_del != NULL)
	{
		map = *map_to_del;
		while (i < map->size)
		{
			if (map->bucket[i] != NULL)
				darray_clear_destroy((t_darray**)&(map->bucket[i]), &del_node);
			i++;
		}
		ft_memdel((void**)&(map->bucket));
		ft_memdel((void**)map_to_del);
	}
}

