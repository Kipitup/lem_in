/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/02 16:30:55 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		remove_link_used_both_way(t_graph *prev, t_graph *curr)
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
	}
}

void		handle_link_used_both_way(t_lemin *lemin)
{
	t_solution	*prev;

	//save all valid paths

//	lemin->result->next = init_new_solution();
	prev = lemin->result;
	lemin->result = lemin->result->next;
	//need to had a pointer *prev in the t_solution so we can navigate easily
	remove_link_used_both_way(prev->graph, lemin->result->graph);
}
