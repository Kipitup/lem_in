/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_path_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 10:37:12 by francis           #+#    #+#             */
/*   Updated: 2020/04/16 14:45:48 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	check_start_and_end(t_path *path, size_t end)
{
	int8_t	ret;
	t_path	*begin;

	ret = FAILURE;
	begin = path;
	if (path->vertex == 0)
	{
		while (path->next != NULL)
			path = path->next;
		if (path->vertex == end)
			ret = SUCCESS;
	}
	path = begin;
	return (ret);
}

int8_t			is_path_valid(t_graph *graph, t_path *path)
{
	t_adj_node	*node;
	size_t		src;
	int8_t		ret;

	src = 0;
	ret = check_start_and_end(path, graph->size - 1);
	while (src < graph->size)
	{
		node = graph->array[src].head;
		while (node != NULL && ret == SUCCESS)
		{
			if (src <= node->dest)
			{
				if (is_link_used_both_way(graph, src, node->dest) == TRUE)
					ret = FAILURE;
			}
			node = node->next;
		}
		src++;
	}
	return (ret);
}
