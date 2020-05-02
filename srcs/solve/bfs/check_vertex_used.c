/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertex_used.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 10:16:12 by francis           #+#    #+#             */
/*   Updated: 2020/05/02 13:37:04 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static uint8_t	update_link_before_vertex(t_solution *sol, size_t current,
		size_t vertex_index)
{
	t_adj_list	node;
	t_adj_node	*link;
	size_t		nb_available;
	uint8_t		ret;

	nb_available = 0;
	ret = FALSE;
	node = sol->graph->array[current];
	while (node.head != NULL)
	{
		if (node.head->available == 0)
			nb_available++;
		node.head = node.head->next;
	}
	if (nb_available > 1)
	{
		link = get_link(sol->graph, current, vertex_index);
		if (link != NULL)
		{
			link->available = USED_MULTIPLE;
			ret = TRUE;
		}
	}
	return (ret);
}

static uint8_t	update_link_after_vertex(t_solution *sol, size_t next,
		size_t vertex_index)
{
	t_adj_list	node;
	t_adj_node	*link;
	size_t		nb_available;
	uint8_t		ret;

	nb_available = 0;
	ret = FALSE;
	node = sol->graph->array[next];
	while (node.head != NULL)
	{
		if (node.head->available == 0)
			nb_available++;
		node.head = node.head->next;
	}
	if (nb_available > 1)
	{
		link = get_link(sol->graph, vertex_index, next);
		if (link != NULL)
		{
			link->available = USED_MULTIPLE;
			ret = TRUE;
		}
	}
	return (ret);
}

static uint8_t	check_link_vertex_used_multiple(t_solution *sol,
		size_t vertex_index, size_t path_i)
{
	t_path	*current;
	t_path	*next;
	uint8_t	ret;

	ret = FALSE;
	current = sol->path->contents[path_i];
	next = current->next;
	while (next->vertex != vertex_index)
	{
		current = current->next;
		next = current->next;
	}
	ret = update_link_before_vertex(sol, current->vertex, vertex_index);
	next = next->next;
	ret = update_link_after_vertex(sol, next->vertex, vertex_index);
	return (ret);
}

static uint8_t	find_path_with_vertex(t_solution *sol, size_t vertex_index, size_t path_index)
{
	t_path	*path;
	uint8_t	ret;

	path = sol->path->contents[path_index];
	ret = FALSE;
	while (path != NULL)
	{
		if (path->vertex == vertex_index)
		{
			ret = check_link_vertex_used_multiple(sol, vertex_index, path_index);
			break ;
		}
		path = path->next;
	}
	return (ret);
}

void			check_vertex_used(t_solution *sol)
{
	t_graph	*graph;
	t_path	*path_removed;
	size_t	path_index;
	size_t	vertex_index;
	uint8_t	ret;

	graph = sol->graph;
	vertex_index = 1;
	path_index = 0;
	ret = FALSE;
	while (vertex_index < graph->size)
	{
		if (graph->array[vertex_index].usable > 1)
		{
			path_index = sol->path->end;
			ret = find_path_with_vertex(sol, vertex_index, path_index);
			if (ret == TRUE)
				reset_vertex_usable_and_link(sol->graph, sol->path->contents[path_index], vertex_index);
		}
		vertex_index++;
	}
	if (path_index != 0)
	{
		path_removed = darray_remove(sol->path, path_index);
		clean_lst_path(path_removed);
	}
}
