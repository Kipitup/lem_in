/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:49:52 by francis           #+#    #+#             */
/*   Updated: 2020/04/09 14:44:49 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_links(t_adj_list node)
{
	while (node.head != NULL)
	{
		ft_printf("dest = %d\t", node.head->dest);
		ft_printf("available = %d\n", node.head->available);
		node.head = node.head->next;
	}
}

void	print_path(t_path *path)
{
	t_path		*tmp;

	if (path != NULL)
	{
		ft_printf("BFS path found:\n");
		tmp = path;
		ft_printf("path: ");
		while (tmp != NULL)
		{
			if (tmp->vertex == 0)
				ft_printf("%d", tmp->vertex);
			else
				ft_printf(" -> %d", tmp->vertex);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}
