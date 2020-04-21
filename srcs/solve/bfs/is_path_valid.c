/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_path_valid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 10:37:12 by francis           #+#    #+#             */
/*   Updated: 2020/04/21 17:04:56 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint8_t			link_used_both_ways(t_graph *graph)
{
	t_adj_node	*current;
	size_t		i;
	uint8_t		ret;

	ret = FALSE;
	i = 0;
	if (graph != NULL)
	{
		while (i < graph->size)
		{
			current = graph->array[i].head;
			while (current != NULL)
			{
				if (is_link_used_both_way(graph, i, current->dest) == TRUE)
					ret = TRUE;
				current = current->next;
			}
			i++;
		}
	}
	return (ret);
}

uint8_t			is_path_valid(t_graph *graph, t_path *path)
{
	t_path		*begin;
	t_path		*nx;
	size_t		end;
	uint8_t		ret;

	begin = path;
	ret = TRUE;
	end = graph->size - 1;
	if (path->vertex == 0)
	{
		while (path->next != NULL)
		{
			nx = path->next;
			if (is_link_used_both_way(graph, path->vertex, nx->vertex) == TRUE)
				ret = FALSE;
			path = path->next;
		}
		if (path->vertex != end)
			ret = FALSE;
	}
	path = begin;
	return (ret);
}
