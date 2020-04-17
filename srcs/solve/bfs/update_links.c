/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:25:32 by francis           #+#    #+#             */
/*   Updated: 2020/04/15 10:32:39 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reset_links(t_graph *graph)
{
	t_adj_node	*tmp;
	size_t		i;

	i = 0;
	while (i < graph->size)
	{
		tmp = graph->array[i].head;
		while (tmp != NULL)
		{
			tmp->available = OPEN;
			tmp = tmp->next;
		}
		i++;
	}
}

void	update_links(t_solution *sol)
{
	t_path		*path;
	t_path		*current;
	t_path		*next;
	t_adj_node	*link;
	size_t		i;

	i = 0;
	reset_links(sol->graph);
	while (i <= sol->path->end)
	{
		path = sol->path->contents[i];
		current = path;
		while (current->next != NULL && current->vertex != sol->graph->size - 1)
		{
			next = current->next;
			link = get_link(sol->graph, current->vertex, next->vertex);
			if (link != NULL)
				link->available = CLOSED;
			current = current->next;
		}
		i++;
	}
}

void	update_links_with_last_wrong_path(t_solution *sol, t_path *wrong_path)
{
	t_adj_node	*link;
	t_path		*current;
	t_path		*next;

	update_links(sol);
	current = wrong_path;
	while (current->next != NULL)
	{
		next = current->next;
		link = get_link(sol->graph, current->vertex, next->vertex);
		if (link != NULL)
			link->available = CLOSED;
		current = current->next;
	}
}
