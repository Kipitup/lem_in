/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:29:03 by fkante            #+#    #+#             */
/*   Updated: 2020/03/09 16:14:36 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "hashmap.h"

int8_t		hashmap_setup(t_lemin *lemin)
{
	t_hashmap	*hashmap;
	char		**table_of_rooms;
	size_t		index;
	int8_t		ret;

	t_hashnode	*node;
	node = NULL;

	index = 0;
	ret = FAILURE;
	hashmap = hashmap_create(NULL, NULL);
	if (hashmap != NULL)
	{
		table_of_rooms = ft_strsplit(lemin->room->str, '\n');
		if (table_of_rooms != NULL)
		{
			while (table_of_rooms[index] != NULL)
			{
				ret = hashmap_set(hashmap, table_of_rooms[index], 0);
				index++;
			}
		}
		index = 0;
		while (table_of_rooms[index] != NULL)
		{
			node = hashmap_get(hashmap, table_of_rooms[index]);
			print_node(node);
			index++;
		}
	}
		return (ret);
}
