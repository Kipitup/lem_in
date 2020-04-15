/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/04/15 11:15:51 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_sol(t_lemin *lemin)
{
	t_solution	*sol;

	lemin->result = ft_memalloc(sizeof(t_solution));
	if (lemin->result != NULL && lemin->link != NULL)
	{
		sol = lemin->result;
		sol->path = darray_create(sizeof(t_path*), DEFAULT_ARRAY_SIZE);
		sol->graph = dup_adj_list(lemin->link);
		sol->prev = NULL;
		sol->next = NULL;
	}
}

t_solution	*init_new_solution(t_lemin *lemin)
{
	t_solution	*new_sol;

	if (lemin != NULL)
	{
		new_sol = ft_memalloc(sizeof(t_solution));
		if (new_sol != NULL && lemin->link != NULL)
		{
			new_sol->path = darray_create(sizeof(t_path*), DEFAULT_ARRAY_SIZE);
			new_sol->graph = dup_adj_list(lemin->link);
			new_sol->prev = NULL;
			new_sol->next = NULL;
		}
	}
	return (new_sol);
}
