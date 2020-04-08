/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_store_and_repath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:47:29 by francis           #+#    #+#             */
/*   Updated: 2020/04/08 18:02:55 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	lstadd(t_path **alst, t_path *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

static size_t find_next_vertex(t_graph *graph, size_t index)
{
	t_adj_list	current_vertex;
	ssize_t		distance_orig;
	ssize_t		next_vertex;

	current_vertex = graph->array[index];
	distance_orig = current_vertex.distance;
	while (current_vertex.head != NULL)
	{
		next_vertex = current_vertex.head->dest;
		if (graph->array[next_vertex].distance == distance_orig - 1)
			break ;
		current_vertex.head = current_vertex.head->next;
	}
	return ((size_t)next_vertex);
}

static t_path	*trace_path_and_update_links(t_graph *graph)
{
	t_path	*path;
	t_path	*new_step;
	size_t	vertex;
	size_t	index;

	index = graph->size - 1;
	path = ft_memalloc(sizeof(t_path));
	if (path != NULL)
	{
		path->vertex = index;
		while (index > 0)
		{
			vertex = find_next_vertex(graph, index);
			new_step = ft_memalloc(sizeof(t_path));
			if (new_step != NULL)
				new_step->vertex = vertex;
			lstadd(&path, new_step);
			index = vertex;
		}
	}
//	update_links(graph, path);
	return (path);
}

int8_t			store_path_and_reset(t_solution *sol)
{
	t_darray	*array;
	t_path		*path_found;
	int8_t		ret;

	array = sol->path;
	ret = FAILURE;
	path_found = trace_path_and_update_links(sol->graph);
	if (path_found != NULL)
	{
		if (array->contents[0] == NULL)
			ret = darray_set(array, 0, (void*)path_found);
		else
			ret = darray_push(array, (void*)path_found);
	}
	return (ret);
}
