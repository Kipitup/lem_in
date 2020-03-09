/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:54:26 by amartino          #+#    #+#             */
/*   Updated: 2020/03/09 14:17:30 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_adj_node		*new_adj_list_node(size_t dest)
{
	t_adj_node		*new_node;

	new_node = ft_memalloc(sizeof(t_adj_node));
	if (new_node != NULL)
		new_node->dest = dest;
	return (new_node);
}

int8_t			add_edge(t_graph *graph, size_t src, size_t dest)
{
	t_adj_node		*new_node;

	if (graph == NULL)
		return (FAILURE);
	new_node = new_adj_list_node(dest);
	if (new_node == NULL)
		return (FAILURE);
	new_node->next = graph->array[src].head;
	graph->array[src].head = new_node;

	new_node = new_adj_list_node(src);
	if (new_node == NULL)
		return (FAILURE);
	new_node->next = graph->array[dest].head;
	graph->array[dest].head = new_node;
	return (SUCCESS);
}

t_graph			*init_graph(size_t size)
{
	t_graph		*graph;

	graph = ft_memalloc(sizeof(t_graph));
	if (graph != NULL)
	{
		graph->size = size;
		graph->array = ft_memalloc(size * sizeof(t_adj_list));
		if (graph->array == NULL)
			ft_memdel((void**)&graph);
	}
	return (graph);
}

void			print_link(t_graph *graph)
{
	t_adj_node	*node;
	size_t		i;

	i = 0;
	while (i < graph->size)
	{
		ft_printf("vertex %d\nhead", i);
		node = graph->array[i].head;
		while (node != NULL)
		{
			ft_printf(" -> %d", node->dest);
			node = node->next;
		}
		ft_printf("\n");
		i++;
	}
}

void	clean_recurse(t_adj_node **node)
{
	if (node != NULL && *node != NULL)
	{
		while ((*node)->next != NULL)
			clean_recurse(&((*node)->next));
		ft_memdel((void**)node);
	}
}

void	clean_graph(t_graph **graph)
{
	size_t		i;

	i = 0;
	if (graph != NULL && *graph != NULL)
	{
		while (i < (*graph)->size)
		{
			clean_recurse(&((*graph)->array[i].head));
			i++;
		}
		ft_memdel((void**)&((*graph)->array));
		ft_memdel((void**)graph);
	}
}
