/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:27:35 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 18:04:25 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "darray.h"
#include "libft.h"

static void	*get_node(t_hashmap *map, t_hashnode *node,
						void *key, uint32_t hash)
{
	t_darray	*array;
	size_t		index_bucket;
	size_t		i;

	index_bucket = hash % DEFAULT_NB_OF_BUCKETS;
	array = map->bucket[index_bucket];
	i = 0;
	if (array != NULL && key != NULL)
	{
		while (i <= array->end)
		{
			node = darray_get(array, i);
			if (node != NULL)
			{
				if (node->hash == hash && map->compare(node->key, key) == TRUE)
					break ;
			}
			i++;
		}
	}
	else
		ft_perror_void(ARRAY_KEY_NULL, STD_ERR);
	return (node);
}

void		*hashmap_get(t_hashmap *map, void *key)
{
	t_hashnode	*node;
	uint32_t	hash;

	node = NULL;
	if (map != NULL)
	{
		hash = map->hash(key, ft_strlen((char*)key));
		node = get_node(map, node, key, hash);
		if (node == NULL)
			ft_perror_failure(NODE_SEARCH_NULL, STD_ERR);
	}
	else
		ft_perror_void(MAP_NULL, STD_ERR);
	return (node);
}
