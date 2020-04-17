/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:45:44 by amartino          #+#    #+#             */
/*   Updated: 2020/04/17 12:36:42 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_lemin(t_lemin **lemin)
{
	if (lemin != NULL && *lemin != NULL)
	{
		vct_del(&((*lemin)->output));
		del_map(&((*lemin)->room));
		clean_adj_graph(&((*lemin)->link));
	//	clean_adj_graph(&((*lemin)->result->graph));
		vct_del(&((*lemin)->start));
		vct_del(&((*lemin)->end));
	//	ft_memdel((void**)&((*lemin)->result));
		ft_memdel((void**)lemin);
	}
}

void	clean_state_machine(t_st_machine **sm)
{
	if (sm != NULL && *sm != NULL)
		ft_memdel((void**)sm);
}

/*
**	all_path was not malloc in network. Is is only a reference from another
**	structure (t_solution). So no need to free it.
*/
void		clean_network(t_network **net)
{
	if (net != NULL && *net != NULL)
	{
		if ((*net)->flow != NULL)
			free((*net)->flow);
		(*net)->flow = NULL;
		(*net)->all_path = NULL;
		ft_memdel((void**)net);
	}
}

