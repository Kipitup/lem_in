/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 13:11:47 by francis           #+#    #+#             */
/*   Updated: 2020/05/10 12:09:08 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		remove_from_queue(t_graph *queue)
{
	if (queue != NULL && queue->array[0].head != NULL)
	{
		if (is_vertex_visited_queue(queue, queue->array[0]) == FALSE)
		{
			if (queue->array[1].head == NULL)
				add_edge_one_way(queue, 1, queue->array[0].head->dest);
			else
				add_edge_rear(queue, 1, queue->array[0].head->dest);
		}
		remove_edge_one_way(queue, 0, queue->array[0].head->dest);
	}
}

static void		add_to_queue(t_graph *queue, t_adj_list node)
{
	if (queue != NULL)
	{
		if (queue->array[0].head == NULL && node.head->available == OPEN)
		{
			add_edge_one_way(queue, 0, node.head->dest);
			node.head->available = CLOSED;
		}
		else if (node.distance != UNVISITED && node.head->available == OPEN)
		{
			add_edge_rear(queue, 0, node.head->dest);
			node.head->available = CLOSED;
		}
	}
}

static uint8_t	set_distance(t_adj_list node, t_graph *graph)
{
	size_t	next_node;
	uint8_t	ret;

	ret = FALSE;
	if (graph != NULL && node.head != NULL)
	{
		if (node.head->available == OPEN)
		{
			next_node = node.head->dest;
			if (graph->array[next_node].distance == UNVISITED)
			{
				graph->array[next_node].distance = node.distance + 1;
				ret = TRUE;
			}
		}
	}
	return (ret);
}

static void		queue_management(t_adj_list nde, t_graph *que, t_solution *sol)
{
	while (nde.head != NULL)
	{
		if (set_distance(nde, sol->graph) == TRUE)
			add_to_queue(que, nde);
		else
			nde.head = nde.head->next;
	}
	remove_from_queue(que);
}

int8_t			bfs(t_solution *sol)
{
	t_adj_list	node;
	t_graph		*queue;
	int8_t		ret;

	ret = FAILURE;
	if (sol != NULL)
	{
		queue = init_queue(sol->graph);
		if (queue != NULL)
		{
			node = next_vertex(sol->graph, queue);
			while (queue->array[0].head != NULL && ret != SUCCESS)
			{
				queue_management(node, queue, sol);
				node = next_vertex(sol->graph, queue);
				if (end_room_visited(sol->graph) == TRUE)
					ret = SUCCESS;
			}
		}
		else
			ret = FAILED_INIT_QUEUE;
	}
	clean_adj_graph(&queue);
	return (ret);
}
