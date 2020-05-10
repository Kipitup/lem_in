/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_store_and_repath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:47:29 by francis           #+#    #+#             */
/*   Updated: 2020/05/10 15:12:26 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	find_next_vertex(t_graph *graph, size_t index)
{
	t_adj_list	current;
	t_adj_node	*link;
	ssize_t		distance_orig;
	ssize_t		next;

	current = graph->array[index];
	distance_orig = current.distance;
	while (current.head != NULL)
	{
		next = current.head->dest;
		if (graph->array[next].distance == distance_orig - 1)
		{
			link = get_link(graph, next, index);
			if (link->available == CLOSED)
			{
				graph->array[next].usable++;
				break ;
			}
		}
		current.head = current.head->next;
	}
	return ((size_t)next);
}

/*
**	Becareful, the name of the path is not malloc. So do no free it from here.
**	just put it to NULL
*/

static uint8_t	create_and_add_step(t_solution *sol, t_path **path,
		size_t vertex, size_t len)
{
	t_path	*new_step;
	uint8_t	ret;

	ret = FALSE;
	if ((new_step = ft_memalloc(sizeof(t_path))) != NULL)
	{
		new_step->vertex = vertex;
		new_step->name = sol->graph->array[vertex].name;
		new_step->len = len;
		lstadd(path, new_step);
		ret = TRUE;
	}
	return (ret);
}

static t_path	*trace_path(t_solution *sol)
{
	t_path	*path;
	size_t	index;
	size_t	vertex;
	size_t	len;

	index = sol->graph->size - 1;
	len = 0;
	if ((path = ft_memalloc(sizeof(t_path))) != NULL)
	{
		path->vertex = index;
		path->name = sol->graph->array[index].name;
		while (index > 0)
		{
			vertex = find_next_vertex(sol->graph, index);
			if (create_and_add_step(sol, &path, vertex, ++len) == TRUE)
				index = vertex;
			else
			{
				clean_lst_path((void*)path);
				path = NULL;
				break ;
			}
		}
	}
	return (path);
}

int8_t			store_valid_path_and_reset(t_solution *sol,
		size_t *used_multiple)
{
	t_darray	*array;
	t_path		*path_found;
	int8_t		ret;

	array = sol->path;
	ret = FAILURE;
	if ((path_found = trace_path(sol)) != NULL)//what if path is null
	{
		update_links_with_last_path(sol, path_found);
		if (is_path_valid(sol->graph, path_found) == TRUE)
		{
			ret = darray_push(array, (void*)path_found);
			check_vertex_used(sol, used_multiple);
		}
		else
		{
			clean_lst_path((void*)path_found);
			path_found = NULL;
		}
	}
	reset_distance(sol->graph);
	return (ret);
}
