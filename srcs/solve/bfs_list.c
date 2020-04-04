/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 13:11:47 by francis           #+#    #+#             */
/*   Updated: 2020/04/04 23:21:50 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_adj_list	*next_vertex(t_graph *graph, t_graph *queue)
{
	t_adj_list	*node;

	node = get_vertex(graph, queue->array[0].head->dest);
	return (node);
}

static size_t		get_index_last_vertex(t_graph *queue)
{
    size_t      index;
    t_adj_node  *tmp;

    index = 0;
    if (queue->array[0].head != NULL)
    {
        tmp = queue->array[0].head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
            index++;
        }
    }
    return (index);
}

static void			add_to_queue(t_graph *queue, t_adj_list *node, size_t step)
{
    size_t      index;

    index = get_index_last_vertex(queue);
	(void)index;
	if (queue != NULL && node != NULL && node->usable != VISITED)
    {
        if (queue->array[0].head == NULL)
            add_edge_one_way(queue, 0, node->head->dest);
        else
            add_edge_rear(queue, 0, node->head->dest);
        node->distance = step;
		if (node->head->next == NULL)
            node->usable = VISITED;
    }
}

static void     remove_from_queue(t_graph *queue)
{
    if (queue != NULL)
    {
        remove_edge_one_way(queue, 0, queue->array[0].head->dest);
    }
}

int8_t				bfs_list(t_solution *sol)
{
    t_graph     *queue;
    t_adj_list  *node;
    int8_t      ret;
    size_t      step;

    ret = START;
    step = 0;
    queue = init_graph(1);
    if (queue != NULL)
    {
        node = get_vertex(sol->graph, 0);
        while (queue != NULL && ret != END)
        {
            while (node->head != NULL)
            {
                add_to_queue(queue, node, step);
                node->head = node->head->next;
            }
			print_adj_list(queue);
			node = next_vertex(sol->graph, queue);
			remove_from_queue(queue);
            step++;
			if (queue->array[0].head->dest == sol->graph->size - 1)
				ret = END;
        }
		print_adj_node(&(sol->graph->array[4]));
    }
    return (0);
}
