/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 20:27:33 by francis           #+#    #+#             */
/*   Updated: 2020/04/05 20:51:30 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t		is_distance_zero(t_adj_list *node)
{
	int8_t	ret;

	ret = TRUE;
	if (node != NULL && node->distance != 0)
		ret = FALSE;
	return (ret);
}

void		add_step(t_adj_list *node, size_t step)
{
	if (node != NULL && node->distance == 0)
		node->distance = step;
}

t_adj_list	next_vertex(t_graph *graph, t_graph *queue)
{
	t_adj_list	node;

	node = get_vertex(graph, queue->array[0].head->dest);
	return (node);
}

t_graph		*init_queue(void)
{
	t_graph		*queue;

	queue = init_graph(2);
	//init start node ? to avoid duplicate of 0 in queue 
	return (queue);
}
