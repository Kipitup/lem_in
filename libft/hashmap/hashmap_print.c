/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 18:00:01 by fkante            #+#    #+#             */
/*   Updated: 2020/03/06 17:58:14 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "darray.h"
#include "libft.h"

void	print_node(t_hashnode *node)
{
	if (node != NULL)
		ft_printf("--> node:\n\t- key: %s\n\t- data: %s\n\t- hash: %u\n",
				(char*)node->key, (char*)node->data, node->hash);
}
