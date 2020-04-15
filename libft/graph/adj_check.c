/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 10:11:57 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/14 09:06:30 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "libft.h"

/*
**	Get the link between vertices src and dest and check his availability
*/
int8_t			is_link_available(t_graph *graph, size_t src, size_t dest)
{
	t_adj_node	*node;
	
	node = get_link(graph, src, dest);
	if (node != NULL)
		return (node->available);
	return (FAILURE);
}

/*
**	Check if the edge between vertices src and dest is used in both direction.
*/
int8_t			is_link_used_both_way(t_graph *graph, size_t src, size_t dest)
{
	int8_t		ret1;
	int8_t		ret2;
	
	ret1 = is_link_available(graph, src, dest);
	ret2 = is_link_available(graph, dest, src);
	if (ret1 == 1 && ret2 == 1)
		return (TRUE);
	else if (ret1 == FAILURE || ret2 == FAILURE)
		return (FAILURE);
	else
		return (FALSE);
}
