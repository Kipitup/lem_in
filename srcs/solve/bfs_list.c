/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 13:11:47 by francis           #+#    #+#             */
/*   Updated: 2020/04/05 21:04:59 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t		is_vertex_visited_queue(t_graph *queue, t_adj_list node)
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

static int8_t		is_vertex_in_queue(t_graph *queue, t_adj_list node)
{
	t_adj_list	copy_queue;
	t_adj_node	*tmp;
	size_t		next_node;
	int8_t		ret;

	ret = FALSE;
	next_node = node.head->dest;
	copy_queue = queue->array[0];
	if (copy_queue.head != NULL)
	{
		tmp = copy_queue.head;
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
	if (queue != NULL)
	{
		if (queue->array[1].head == NULL)
			add_edge_one_way(queue, 1, queue->array[0].head->dest);
		else if (is_vertex_visited_queue(queue, queue->array[0]) == FALSE)
			add_edge_rear(queue, 1, queue->array[0].head->dest);
		remove_edge_one_way(queue, 0, queue->array[0].head->dest);
	}
}

static void		add_to_queue(t_graph *queue, t_adj_list node, t_graph *graph, size_t step)
{
	if (queue != NULL && node.usable != VISITED)
	{
		if (queue->array[0].head == NULL)
			add_edge_one_way(queue, 0, node.head->dest);
		else if (is_vertex_visited_queue(queue, node) == FALSE && is_vertex_in_queue(queue, node) != VISITED)
			add_edge_rear(queue, 0, node.head->dest);
		if (node.head->dest != 0 && is_distance_zero(&(graph->array[node.head->dest])) == TRUE)
		{
			add_step(&(graph->array[node.head->dest]), step);
		}
		if (node.head->next == NULL)
			node.usable = VISITED;
	}
}
/*
 ** DONT FORGET Protection in get_vertex for the node, also in next_vertex
 */
int8_t				bfs_list(t_solution *sol)
{
	t_graph		*queue;
	t_adj_list	node;
	size_t		step;
	int8_t		ret;

	ret = START;
	step = 0;
	queue = init_queue();
	if (queue != NULL)
	{
		node = get_vertex(sol->graph, 0);
		while (queue != NULL && ret != END)
		{
			step++;
			while (node.head != NULL)
			{
				add_to_queue(queue, node, sol->graph, step);
				node.head = node.head->next;
			}
			ft_printf("---------------------------\n");
			node = next_vertex(sol->graph, queue);
			print_queue(queue);
			remove_from_queue(queue);
			if (queue->array[0].head->dest == sol->graph->size - 1)
				ret = END;
		}
		//for (size_t i = 0; i < sol->graph->size; i++)
		//	print_adj_node(sol->graph->array[i]);
	}
	return (0);
}
