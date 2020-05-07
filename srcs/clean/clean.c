/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:45:44 by amartino          #+#    #+#             */
/*   Updated: 2020/05/07 14:57:02 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_lst_path(void *path)
{
	t_path *tmp;

	while (path != NULL)
	{
		tmp = ((t_path*)path)->next;
		free(path);
		path = (tmp != NULL) ? tmp->next : tmp;
	}
}

void	clean_all_solution(t_lemin **lemin)
{
	t_solution *tmp;
	
	while ((*lemin)->result != NULL)
	{
		clean_adj_graph(&((*lemin)->result->graph));
		darray_clear_destroy(&((*lemin)->result->path), &clean_lst_path); //protection if init of graph worked but dup didnt
		clean_network(&((*lemin)->result->net));
		tmp = (*lemin)->result;
		(*lemin)->result = (*lemin)->result->next;
		ft_memdel((void**)&tmp);
	}
}

void	clean_lemin(t_lemin **lemin)
{
	if (lemin != NULL && *lemin != NULL)
	{
		vct_del(&((*lemin)->output));
		del_map(&((*lemin)->room));
		clean_adj_graph(&((*lemin)->link));
		clean_all_solution(lemin);
		vct_del(&((*lemin)->start));
		vct_del(&((*lemin)->end));
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
