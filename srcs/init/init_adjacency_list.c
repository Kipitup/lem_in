/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_adjacency_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:48:39 by francis           #+#    #+#             */
/*   Updated: 2020/05/18 23:48:57 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				init_adjacency_list(t_st_machine *sm)
{
	size_t	size;

	size = sm->lemin->room->nb_of_elem;
	if (size == 0)
		sm->state = NO_ROOM;
	else if (sm->lemin->start == NULL)
		sm->state = NO_START;
	else if (sm->lemin->end == NULL)
		sm->state = NO_END;
	else
	{
		sm->lemin->link = init_graph(size);
		if (sm->lemin->link == NULL && sm->lemin->result->graph)
			sm->state = ADJ_LIST_MALLOC;
	}
}
