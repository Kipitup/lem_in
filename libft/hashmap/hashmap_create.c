/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:23:13 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 13:23:09 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "darray.h"
#include "libft.h"

t_hashnode	*hash_node_create(void *key, void *data, uint32_t hash)
{
	t_hashnode	*node;

	node = ft_memalloc(sizeof(t_hashnode));
	if (node != NULL)
	{
		node->key = key;
		node->data = data;
		node->hash = hash;
	}
	return (node);
}

t_hashmap	*hashmap_create(t_hash_comp compare, t_hash_func hash)
{
	t_hashmap	*map;

	map = ft_memalloc((sizeof(t_hashmap)));
	if (map != NULL)
	{
		map->compare = (compare == NULL) ? &default_compare : compare;
		map->hash = (hash == NULL) ? &ft_hash_void_data : hash;
		map->size = DEFAULT_NB_OF_BUCKETS;
		map->nb_of_elem = 0;
		map->nb_collision = 0;
		map->bucket = ft_memalloc(DEFAULT_NB_OF_BUCKETS * (sizeof(t_darray*)));
		if (map->bucket == NULL)
		{
			ft_perror_void(BUCKET_ALLOC_FAIL, STD_ERR);
			del_map(&map);
		}
	}
	else
		ft_perror_void(MAP_ALLOC_FAIL, STD_ERR);
	return (map);
}
