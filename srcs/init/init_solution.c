/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/05/07 14:37:55 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_solution(t_lemin *lemin)
{
	t_solution	*sol;

	if (lemin != NULL)
	{
		lemin->result = ft_memalloc(sizeof(t_solution));
		if (lemin->result != NULL && lemin->link != NULL)
		{
			sol = lemin->result;
			sol->path = darray_create(sizeof(t_path*), DEFAULT_ARRAY_SIZE);
			sol->graph = dup_adj_list(lemin->link);
		}
	}
}

t_solution	*init_new_solution(t_lemin *lemin)
{
	t_solution	*new_sol;

	new_sol = NULL;
	if (lemin != NULL)
	{
		new_sol = ft_memalloc(sizeof(t_solution));
		if (new_sol != NULL && lemin->link != NULL)
		{
			new_sol->path = darray_create(sizeof(t_path*), DEFAULT_ARRAY_SIZE);
			new_sol->graph = dup_adj_list(lemin->result->graph);
		}
	}
	return (new_sol);
}
