/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 20:27:33 by francis           #+#    #+#             */
/*   Updated: 2020/04/25 09:02:05 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint8_t		end_room_visited(t_graph *graph)
{
	size_t	end_room_index;
	uint8_t	ret;

	end_room_index = graph->size - 1;
	ret = TRUE;
	if (graph->array[end_room_index].distance == UNVISITED)
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

	if (queue->array[0].head != NULL)
		node = get_vertex(graph, queue->array[0].head->dest);
	else
		node.head = NULL;
	return (node);
}

t_graph		*init_queue(t_graph *graph_orig)
{
	t_graph		*queue;
	t_adj_node	*start_node;

	queue = init_graph(2);
	if (queue != NULL && graph_orig != NULL)
	{
		start_node = ft_memalloc(sizeof(t_adj_node));
		if (start_node != NULL)
		{
			start_node->dest = 0;
			queue->array[0].head = start_node;
			queue->array[0].distance = 0;
			graph_orig->array[0].distance = 0;
		}
	}
	return (queue);
}
