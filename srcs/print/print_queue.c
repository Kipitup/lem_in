/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 08:56:13 by francis           #+#    #+#             */
/*   Updated: 2020/04/25 08:56:18 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_queue(t_graph *queue)
{
	t_adj_node	*node;

	if (queue != NULL)
	{
		ft_printf("Queue\nhead");
		node = queue->array[0].head;
		while (node != NULL)
		{
			ft_printf(" -> %d", node->dest);
			node = node->next;
		}
		ft_printf("\n");
		ft_printf("Visited\nhead");
		node = queue->array[1].head;
		while (node != NULL)
		{
			ft_printf(" -> %d", node->dest);
			node = node->next;
		}
		ft_printf("\n");
	}
}
