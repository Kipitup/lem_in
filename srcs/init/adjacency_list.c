/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:54:26 by amartino          #+#    #+#             */
/*   Updated: 2020/03/02 18:38:27 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

typedef struct	s_adj_node
{
	size_t			dest;
	struct s_adj_node	*next;
}				t_adj_node;

typedef struct	s_adj_list
{
	t_adj_node			*head;
}				t_adj_list;

typedef struct	s_graph
{
	t_adj_list			*array;
	size_t				size;
}				t_graph;

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

int				main(void)
{
	t_graph		*graph;
	size_t		size;
	int8_t		ret;

	size = 5;
	graph = NULL;
	graph = init_graph(size);
	if (graph != NULL)
	{
		ret = add_edge(graph, 0, 1);
		if (ret != FAILURE)
			ret = add_edge(graph, 0, 4);
		if (ret != FAILURE)
			ret = add_edge(graph, 1, 2);
		if (ret != FAILURE)
			ret = add_edge(graph, 2, 0);
		if (ret != FAILURE)
			ret = add_edge(graph, 3, 4);
		print_link(graph);
	}
	clean_graph(&graph);
	return (0);
}
