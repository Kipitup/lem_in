/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:25:32 by francis           #+#    #+#             */
/*   Updated: 2020/04/09 10:28:14 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_links(t_graph *graph, t_path *path)
{
	t_path		*begin;
	t_path		*next;
	t_path		*current;
	t_adj_node	*tmp;
	
	int i = 0;

	begin = path;
	while (path->next != NULL)
	{
		current = path;
		next = path->next;
		tmp = graph->array[current->vertex].head;
		while (graph->array[current->vertex].head->dest != next->vertex && graph->array[current->vertex].head != NULL)
			graph->array[current->vertex].head = graph->array[current->vertex].head->next;
		graph->array[current->vertex].head->available = CLOSED;
		graph->array[current->vertex].head = tmp;
		i++;
		path = path->next;
	}
	path = begin;
}
