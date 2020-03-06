/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:22:18 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 17:57:29 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"


static char		*allocate_elem(char *elem, char *str_to_insert)
{
	elem = ft_memalloc(ft_strlen(str_to_insert) + 1);
	elem = ft_strcpy(elem, str_to_insert);
	return (elem);
}
static int8_t	test_set_elem(t_hashmap *map)
{
	char		*key_1, *key_2, *key_3;
	char		*data_1, *data_2, *data_3;
	int8_t		ret;

	key_1 = allocate_elem(key_1, "room_start");
	data_1 = allocate_elem(data_1, "room_start_data");
	key_2 = allocate_elem(key_2, "francis");
	data_2 = allocate_elem(data_2, "la room de francis");
	key_3 = allocate_elem(key_3, "alex");
	data_3 = allocate_elem(data_3, "la room de alex");
	ret = hashmap_set(map, key_1, data_1);
	ret = hashmap_set(map, key_2, data_2);
	ret = hashmap_set(map, key_3, data_3);
	return (ret);
}

int				main(void)
{
	t_hashmap	*map;
	t_hashnode	*node;
	void		*key_to_found;
	int8_t		ret;

	map = hashmap_create(NULL, NULL);
	if (map != NULL)
	{
		key_to_found = allocate_elem(key_to_found, "alex");
		ft_printf("key to found\t------- %s\n", key_to_found);
		ret = test_set_elem(map);
		node = hashmap_get(map, key_to_found);
		if (node != NULL)
			ft_printf("{c_green}Node found !{c_end}\n");
		print_node(node);
		ft_printf("ret: %d\n", ret);
		del_map(&map);
	}
	return (0);
}
