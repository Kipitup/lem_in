/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_store_and_repath.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 14:47:29 by francis           #+#    #+#             */
/*   Updated: 2020/04/21 17:58:35 by francis          ###   ########.fr       */
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
static t_path	*trace_path(t_solution *sol)
{
	t_path	*path;
	t_path	*new_step;
	size_t	vertex;
	size_t	index;
	size_t	len;

	index = sol->graph->size - 1;
	len = 0;
	path = ft_memalloc(sizeof(t_path));
	if (path != NULL)
	{
		path->vertex = index;
		path->name = sol->graph->array[index].name;
		while (index > 0)
		{
			vertex = find_next_vertex(sol->graph, index);
			if ((new_step = ft_memalloc(sizeof(t_path))) != NULL)//what if malloc fail
			{
				new_step->vertex = vertex;
				new_step->name = sol->graph->array[vertex].name;
				new_step->len = ++len;
				lstadd(&path, new_step);
				index = vertex;
			}
		}
	}
	return (path);
}

static void		reset_distance(t_graph *graph)
{
	size_t	i;

	i = 0;
	while (i < graph->size)
	{
		graph->array[i].distance = UNVISITED;
		i++;
	}
}

int8_t			store_valid_path_and_reset(t_solution *sol)
{
	t_darray	*array;
	t_path		*path_found;
	int8_t		ret;

	array = sol->path;
	ret = FAILURE;
	if ((path_found = trace_path(sol)) != NULL)// free path if false
	{
		if (is_path_valid(sol->graph, path_found) == TRUE)
		{
			if (array->contents[0] == NULL)
				ret = darray_set(array, 0, (void*)path_found);
			else
				ret = darray_push(array, (void*)path_found);
			update_links(sol);
		}
		else
		{
			update_links_with_last_wrong_path(sol, path_found);
			clean_lst_path(path_found);
		}
	}
	reset_distance(sol->graph);
	return (ret);
}
