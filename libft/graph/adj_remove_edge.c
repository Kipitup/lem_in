/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_remove_edge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 11:14:11 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/02 15:03:01 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "graph.h"
#include "libft.h"

/*
**	Return the adresse of the link just before dest. If there is no previous
**	link (when dest is the fisrt link of the chain), it return the dest link
*/
static t_adj_node	*get_previous_link(t_graph *graph, size_t src, size_t dest)
{
	t_adj_node		*prev;

	prev = graph->array[src].head;
	while (prev != NULL && prev->dest != dest)
	{
		if (prev->next != NULL && prev->next->dest == dest)
			break ;
		prev = prev->next;
	}
	return (prev);
}

/*
**	Remove only the link from src to dest but not from dest to src. Use
**	remove_edge beloz for this.
*/
void				remove_edge_one_way(t_graph *graph, size_t src, size_t dest)
{
	t_adj_node		*prev;
	t_adj_node		*to_del;

	if (graph != NULL)
	{
		prev = get_previous_link(graph, src, dest);
		if (prev != NULL)
		{
			if (prev->dest == dest)
			{
				to_del = graph->array[src].head;
				graph->array[src].head = to_del->next;
			}
			else
			{
				to_del = prev->next;
				prev->next = to_del->next;
			}
			ft_memdel((void**)&to_del);
		}
	}
}

/*
**	Remove the link from src to dest AND from dest to src.
*/
void				remove_edge(t_graph *graph, size_t src, size_t dest)
{
	remove_edge_one_way(graph, src, dest);
	remove_edge_one_way(graph, dest, src);
}
