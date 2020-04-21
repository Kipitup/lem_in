/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 13:11:47 by francis           #+#    #+#             */
/*   Updated: 2020/04/21 14:31:00 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	is_vertex_visited_queue(t_graph *queue, t_adj_list node)
{
	t_adj_list	visited;
	t_adj_node	*tmp;
	size_t		next_node;
	int8_t		ret;

	ret = FALSE;
	next_node = node.head->dest;
	visited = queue->array[1];
	if (visited.head != NULL)
	{
		tmp = visited.head;
		while (tmp->next != NULL && ret == FALSE)
		{
			if (tmp->dest == next_node)
				ret = TRUE;
			tmp = tmp->next;
		}
	}
	return (ret);
}

static void     remove_from_queue(t_graph *queue)
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

static int8_t	set_distance(t_adj_list node, t_graph *graph)
{
	size_t	next_node;
	int8_t	ret;

	ret = FAILURE;
	if (graph != NULL && node.head != NULL)
	{
		if (node.head->available == OPEN)
		{
			next_node = node.head->dest;
			if (graph->array[next_node].distance == UNVISITED)
			{
				graph->array[next_node].distance = node.distance + 1;
				ret = SUCCESS;
			}
		}
	}
	return (ret);
}
/*
 ** DONT FORGET Protection in get_vertex for the node, also in next_vertex
 ** protection in case of failure, need to free queue, also path
 */

int8_t			bfs(t_solution *sol)
{
	t_adj_list	node;
	t_graph		*queue;
	int8_t		ret;

	ret = FAILURE;
	if (sol != NULL)
	{
		queue = init_queue(sol->graph);
		node = next_vertex(sol->graph, queue);
		while (queue->array[0].head != NULL && ret != SUCCESS)
		{
			while (node.head != NULL)
			{
				if (set_distance(node, sol->graph) == SUCCESS)
					add_to_queue(queue, node);
				else
					node.head = node.head->next;
			}
			remove_from_queue(queue);
			node = next_vertex(sol->graph, queue);
			if (end_room_visited(sol->graph) == TRUE)
				ret = SUCCESS;
		}
	}
	clean_adj_graph(&queue);
	return (ret);
}
