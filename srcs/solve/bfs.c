/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/03/11 10:39:17 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_queue          *init_queue(size_t nb_max_elem)
{
    t_queue     *queue;

    queue = ft_memalloc(sizeof(t_queue));
    if (queue != NULL)
    {
        queue->size = 0;
        queue->front = 0;
        queue->limit = nb_max_elem;
        queue->element = ft_memalloc(sizeof(t_adj_list) * nb_max_elem);
    }
    return (queue);
}

static int8_t           queue_empty(t_queue *queue)
{
    int8_t      ret;

    ret = TRUE;
    if (queue->size > 0)
        ret = FALSE;
    return (ret);
}

static void             add_to_queue(t_queue *queue, t_adj_list *node, size_t step)
{
    if (node != NULL)
    {
        if (queue->size == queue->limit)
            ft_perror(QUEUE_FULL, __FILE__, __LINE__);
        else
        {
            if (node->usable == OPEN && node->distance == 0)
            {
                node->distance = step;
                queue->element[queue->size] = node;
                queue->size++;
            }
        }
    }
}

static t_adj_list      *remove_from_queue(t_queue *queue)
{
    t_adj_list  *front_node;

    front_node = NULL;
    if (queue_empty(queue) == TRUE)
        ft_perror(QUEUE_EMPTY, __FILE__, __LINE__);
    else
    {
        front_node = queue->element[queue->front];
        queue->front++;
        if (queue->front > queue->size)
        {
            queue->front = 0;
            queue->size = 0;
        }
        front_node->usable = VISITED;
    }
    return (front_node);
}


int8_t                  bfs(t_graph *graph, t_solution *sol)
{
    t_queue     *queue;
    t_adj_list  *current_node;
    size_t      step;
    int8_t      ret;

    (void)sol;
    step = 0;
    ret = START;
    queue = init_queue(graph->size);
    if (queue != NULL)
    {
        add_to_queue(queue, &(graph->array[0]), step);
        while (queue_empty(queue) == FALSE && ret != END)
        {
            step++;
            print_queue(queue);
            current_node = remove_from_queue(queue);
            while (current_node->head != NULL)
            {
                add_to_queue(queue, &(graph->array[current_node->head->dest]), step);
                if (current_node->head->dest == graph->size - 1)
                    ret = END;
                current_node->head = current_node->head->next;
            }
        }
        for (size_t i = 0; i < graph->size; i++)
        {
            ft_printf("\nPrinting node [%d]:", i);
            print_adj_node(&(graph->array[i]));
        }
    }
    return (0);
}
