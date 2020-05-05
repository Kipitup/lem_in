/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vertex_used.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 10:16:12 by francis           #+#    #+#             */
/*   Updated: 2020/05/05 11:08:58 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_vertex_usable_and_link(t_graph *graph, t_path *path)
{
	t_adj_node	*link;

	if (graph != NULL)
	{
		while (path->next != NULL)
		{
			link = get_link(graph, path->vertex, path->next->vertex);
			if (link != NULL && link->available != USED_MULTIPLE)
				link->available = OPEN;
			graph->array[path->vertex].usable--;
			path = path->next;
		}
	}
	else
		ft_perror(GRAPH_NULL, __FILE__, __LINE__);
}

static uint8_t	block_vertex_link(t_graph *graph, size_t from_vertex,
		size_t to_vertex)
{
	t_adj_list	node;
	t_adj_node	*link;
	size_t		nb_available;
	uint8_t		ret;

	ret = FALSE;
	nb_available = 0;
	node = graph->array[from_vertex];
	while (node.head != NULL)
	{
		if (node.head->available == OPEN)
			nb_available++;
		node.head = node.head->next;
	}
	if (nb_available > 1)
	{
		link = get_link(graph, from_vertex, to_vertex);
		if (link != NULL)
		{
			link->available = USED_MULTIPLE;
			ret = TRUE;
		}
	}
	return (ret);
}

static uint8_t	is_vertex_used_multiple(t_path *current, t_graph *graph)
{
	t_path		*next;
	uint8_t		ret;

	ret = FALSE;
	next = current->next;
	while (next != NULL)
	{
		if (graph->array[next->vertex].usable > 1)
		{
			ret = block_vertex_link(graph, current->vertex, next->vertex);
			current = next;
			next = next->next;
			if (ret == FALSE)
				ret = block_vertex_link(graph, current->vertex, next->vertex);
			else
				block_vertex_link(graph, current->vertex, next->vertex);
		}
		current = next;
		next = next->next;
	}
	return (ret);
}

void			check_vertex_used(t_solution *sol, size_t *used_multiple)
{
	t_path		*path_removed;
	t_path		*path;
	size_t		i_last;
	uint8_t		ret;

	if (sol->path->end != 0)
	{
		i_last = sol->path->end;
		path = ((t_path*)sol->path->contents[i_last])->next;
		ret = is_vertex_used_multiple(path, sol->graph);
		if (ret == TRUE)
		{
			(*used_multiple)++;
			reset_vertex_usable_and_link(sol->graph, path);
			path_removed = darray_remove(sol->path, i_last);
			clean_lst_path((void*)path_removed);
			path_removed = NULL;
		}
	}
}
