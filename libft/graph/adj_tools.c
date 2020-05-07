/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 11:24:03 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/07 10:32:00 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "libft.h"

static int8_t	dup_edge_recurse(t_adj_node	*node, t_graph *duplicate,
		size_t src)
{
	int8_t	ret;

	ret = SUCCESS;
	if (node != NULL)
	{
		ret = dup_edge_recurse(node->next, duplicate, src);	
		if (ret == SUCCESS)
			ret = add_edge_one_way(duplicate, src, node->dest);
		if (ret == SUCCESS && node->available == 2)
			duplicate->array[src].head->available = node->available;
	}
	return (ret);
}

/*
**	Create a duplicate of a given graph, with all his vertices and edges in the
**	exact order.
*/
t_graph			*dup_adj_list(t_graph *graph)
{
	t_graph		*duplicate;
	size_t		i;
	int8_t		ret;

	i = 0;
	duplicate = init_graph(graph->size);
	if (duplicate != NULL)
	{
		while (i < graph->size && duplicate != NULL)
		{
			if (graph->array[i].name != NULL)
				duplicate->array[i].name = ft_strdup(graph->array[i].name);
			ret = dup_edge_recurse(graph->array[i].head, duplicate, i);
			if (ret == FAILURE)
			{
				clean_adj_graph(&duplicate);
				break ;
			}
			i++;
		}
	}
	return (duplicate);
}

int8_t			add_vertex_name(t_graph *graph, size_t i, char *name)
{
	char		*dup_name;

	if (graph != NULL && name != NULL)
	{
		if (graph->array[i].name == NULL)
		{
			dup_name = ft_strdup(name);
			if (dup_name != NULL)
			{
				graph->array[i].name = dup_name;
				return (SUCCESS);
			}
		}
		else
				return (SUCCESS);
	}
	return (FAILURE);
}

//[?] this need protection
t_adj_list		get_vertex(t_graph *graph, size_t src)
{
	t_adj_list	vertex;

	//if (graph != NULL)
	vertex = graph->array[src];
	return (vertex);
}

/*
**	Get the link (edge) between vertices src and dest. If the link does not
**	exist, NULL is return.
*/
t_adj_node		*get_link(t_graph *graph, size_t src, size_t dest)
{
	t_adj_node	*node;

	node = NULL;
	if (graph != NULL)
	{
		node = graph->array[src].head;
		while (node != NULL)
		{
			if (node->dest == dest)
				break;
			node = node->next;
		}
	}
	return (node);
}
