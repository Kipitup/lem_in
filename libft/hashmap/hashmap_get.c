/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:27:35 by fkante            #+#    #+#             */
/*   Updated: 2020/05/10 19:06:31 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "darray.h"
#include "libft.h"

static void	*get_node(t_hashmap *map, void *key, uint32_t hash)
{
	t_darray	*array;
	t_hashnode	*node;
	size_t		index_bucket;
	size_t		i;

	i = 0;
	node = NULL;
	index_bucket = hash % map->size;
	array = map->bucket[index_bucket];
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
			node = NULL;
			i++;
		}
	}
	return (node);
}

/*
**		if (node == NULL)
**			ft_perror_failure(NODE_SEARCH_NULL, __FILE__, __LINE__);
*/
void		*hashmap_get(t_hashmap *map, void *key)
{
	t_hashnode	*node;
	uint32_t	hash;

	node = NULL;
	if (map != NULL)
	{
		hash = map->hash(key, ft_strlen((char*)key));
		node = get_node(map, key, hash);
	}
	else
		ft_perror(MAP_NULL, __FILE__, __LINE__);
	return (node);
}
