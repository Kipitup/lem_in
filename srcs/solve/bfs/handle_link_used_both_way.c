/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_link_used_both_way.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 10:34:48 by francis           #+#    #+#             */
/*   Updated: 2020/04/16 15:16:08 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	remove_link_used_both_way(t_graph *prev, t_graph *curr)
{
	size_t		src;
	t_adj_node	*node;

	src = 0;
	while (src < prev->size)
	{
		node = prev->array[src].head;
		while (node != NULL)
		{
			if (src <= node->dest)
			{
				if (is_link_used_both_way(prev, src, node->dest) == TRUE)
					remove_edge(curr, src, node->dest);
			}
			node = node->next;
		}
		src++;
	}
}

void		handle_link_used_both_way(t_lemin *lemin)
{
	t_solution	*prev;

	lemin->result->next = init_new_solution(lemin);
	prev = lemin->result;
	lemin->result = lemin->result->next;
	lemin->result->prev = prev;
	remove_link_used_both_way(prev->graph, lemin->result->graph);
}
