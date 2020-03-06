/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:22:18 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 11:10:15 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

static char	*allocate_elem(char *elem, char *str_to_insert)
{
	elem = ft_memalloc(ft_strlen(str_to_insert) + 1);
	elem = ft_strcpy(elem, str_to_insert);
	return (elem);
}

int		main(void)
{
	t_hashmap	*map;
	char		*key_1, *key_2, *key_3;
	char		*data_1, *data_2, *data_3;
	int8_t		ret;

	map = hashmap_create(NULL, NULL);
	if (map != NULL)
	{
		key_1 = allocate_elem(key_1, "room_start");
		data_1 = allocate_elem(data_1, "room_start_data");
		key_2 = allocate_elem(key_2, "francis");
		data_2 = allocate_elem(data_2, "la room de francis");
		key_3 = allocate_elem(key_3, "alex");
		data_3 = allocate_elem(data_3, "la room de alex");
		ret = hashmap_set(map, key_1, data_1);
		ret = hashmap_set(map, key_2, data_2);
		ret = hashmap_set(map, key_3, data_3);
		ft_printf("ret: %d\n", ret);
		del_map(&map);
	}
	return (0);
}
