/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_second_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 21:22:36 by francis           #+#    #+#             */
/*   Updated: 2020/05/01 09:45:41 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lstadd(t_path **alst, t_path *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	reset_distance(t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->size)
	{
		graph->array[i].distance = UNVISITED;
		i++;
	}
}

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

void	reset_vertex_usable_and_link(t_graph *graph, t_path *path, size_t vertex_index)
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
				if (link != NULL && link->available != USED_MULTIPLE)
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
