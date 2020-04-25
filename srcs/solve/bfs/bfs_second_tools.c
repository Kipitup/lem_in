/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_second_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 21:22:36 by francis           #+#    #+#             */
/*   Updated: 2020/04/25 09:00:15 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	first_path_with_multiple(t_solution *sol, size_t vertex_index)
{
	t_path	*path;
	size_t	i;

	i = 0;
	if (sol != NULL && sol->path != NULL)
	{
		while (i <= sol->path->end)
		{
			path = sol->path->contents[i];
			while (path != NULL)
			{
				if (path->vertex == vertex_index)
					return (i);
				path = path->next;
			}
			i++;
		}
	}
	return (i);
}

void	reset_vertex_usable(t_graph *graph, t_path *path, size_t vertex_index)
{
	t_adj_node	*link;
	t_path		*next;

	if (graph != NULL)
	{
		while (path != NULL)
		{
			next = path->next;
			if (next != NULL && path->vertex != vertex_index)
			{
				link = get_link(graph, path->vertex, next->vertex);
				if (link != NULL)
					link->available = 0;
			}
			if (path->vertex != 0 && path->vertex != graph->size - 1)
				graph->array[path->vertex].usable--;
			path = path->next;
		}
	}
	else
		ft_perror(GRAPH_NULL, __FILE__, __LINE__);
}
