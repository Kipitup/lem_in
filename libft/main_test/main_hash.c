/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:22:18 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 19:51:53 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

int		main(void)
{
	t_hashmap	*map;
	char		*key;
	char		*data;
	int8_t		ret;
	
	map = hashmap_create(NULL, NULL);
	if (map != NULL)
	{
		key =  ft_memalloc(
		ret = hashmap_set(map, key, "room_start_data");
		ft_printf("ret: %d\n", ret);
		del_map(&map);
	}
	return (0);
}
