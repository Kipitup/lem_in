/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 11:24:03 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/01 12:03:30 by amartinod        ###   ########.fr       */
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
			ret = add_one_sided_edge(duplicate, src, node->dest);
	}
	return (ret);
}

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
			ret = dup_edge_recurse(graph->array[i].head, duplicate, i);
			if (ret == FAILURE)
			{
				clean_graph(&duplicate);
				break ;
			}
			i++;
		}
	}
	return (duplicate);
}

uint8_t				does_link_exist(t_graph *graph, size_t index, size_t dest)
{
	t_adj_node	*node_src;
	uint8_t		ret;

	ret = FALSE;
	if (graph != NULL)
	{
		node_src = graph->array[index].head;
		while (node_src != NULL)
		{
			if (node_src->dest == dest)
			{
				ret = TRUE;
				break;
			}
			node_src = node_src->next;
		}
	}
	return (ret);
}
