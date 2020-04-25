/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertex_used.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 10:16:12 by francis           #+#    #+#             */
/*   Updated: 2020/04/25 09:02:34 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	update_link_before_vertex(t_solution *sol, size_t current,
		size_t vertex_index)
{
	t_adj_list	node;
	t_adj_node	*link;
	size_t		nb_available;

	nb_available = 0;
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
			link->available = USED_MULTIPLE;
	}
}

static void	update_link_after_vertex(t_solution *sol, size_t next,
		size_t vertex_index)
{
	t_adj_list	node;
	t_adj_node	*link;
	size_t		nb_available;

	nb_available = 0;
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
			link->available = USED_MULTIPLE;
	}
}

static void	check_link_vertex_used_multiple(t_solution *sol,
		size_t vertex_index, size_t path_i)
{
	t_path	*current;
	t_path	*next;

	current = sol->path->contents[path_i];
	next = current->next;
	while (next->vertex != vertex_index)
	{
		current = current->next;
		next = current->next;
	}
	update_link_before_vertex(sol, current->vertex, vertex_index);
	next = next->next;
	update_link_after_vertex(sol, next->vertex, vertex_index);
}

static void	find_path_with_vertex(t_solution *sol, size_t vertex_index)
{
	t_path	*path;
	t_path	*path_removed;
	t_path	*begin;
	size_t	i;

	i = first_path_with_multiple(sol, vertex_index) + 1;
	while (i <= sol->path->end)
	{
		path = sol->path->contents[i];
		begin = path;
		while (path != NULL)
		{
			if (path->vertex == vertex_index)
			{
				check_link_vertex_used_multiple(sol, vertex_index, i);
				path_removed = darray_remove(sol->path, i);
				reset_vertex_usable(sol->graph, begin, vertex_index);
				clean_lst_path(path_removed);
				break ;
			}
			path = path->next;
		}
		i++;
	}
}

int8_t		check_vertex_used(t_solution *sol)
{
	t_graph	*graph;
	size_t	i;
	int8_t	ret;

	graph = sol->graph;
	i = 1;
	ret = FAILURE;
	update_links(sol);
	while (i < graph->size)
	{
		if (graph->array[i].usable > 1)
		{
			find_path_with_vertex(sol, i);
			ret = SUCCESS;
		}
		i++;
	}
	return (ret);
}
