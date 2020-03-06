/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:35:14 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 10:52:56 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "darray.h"
#include "libft.h"

static int8_t		push_node(t_hashmap *map, t_hashnode *node, uint32_t hash)
{
	t_darray	*array;
	size_t		index;
	int8_t		ret;
	
	ret = FAILURE;
	index = hash % DEFAULTF_NB_OF_BUCKETS;
	if (map->bucket[index] == NULL)
	{
		array = darray_create(sizeof(t_hashnode*), DEFAULT_ARRAY_SIZE);
		if (array != NULL)
		{
			ret = darray_push(array, (void*)node);
			if (ret == SUCCESS)
				map->bucket[index] = array;
			else
				darray_clear_destroy(&array, &del_node);
		}
	}
	else
	{
		ret = darray_push(map->bucket[index], (void*)node);
		map->nb_collision++;
	}
	return (ret);
}

int8_t				hashmap_set(t_hashmap *map, void *key, void *data)
{
	t_hashnode	*node;
	uint32_t	hash;
	int8_t		ret;

	if (map != NULL)
	{
		hash = map->hash(key, ft_strlen((char*)key));
		node = hash_node_create(key, data, hash);
		print_node(node);
		if (node != NULL)
		{
			ret = push_node(map, node, hash);
			map->nb_of_elem++;
		}
		else
			ret = ft_perror_failure(NODE_NULL, STD_ERR);
	}
	else
		ret = ft_perror_failure(MAP_NULL, STD_ERR);
	return (ret);
}
