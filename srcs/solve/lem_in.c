/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/15 12:01:09 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_in(t_lemin *lemin)
{
	t_solution	*sol;
	int8_t		ret;

	if (lemin->result != NULL)
	{
		ret = SUCCESS;
		sol = lemin->result;
		print_adj_list(sol->graph);
		ft_printf("--------------------------------------\n");
		while (ret == SUCCESS)
		{
			bfs(sol);
			if ((ret = store_valid_path_and_reset(sol)) == FAILURE)
				handle_link_used_both_way(lemin);
		}
		ft_printf("--------------------------------------\n");
		ret = SUCCESS;
		sol = lemin->result;
		print_adj_list(sol->graph);
		if (ret == SUCCESS)
		{
			bfs(sol);
			if ((ret = store_valid_path_and_reset(sol)) == FAILURE)
				handle_link_used_both_way(lemin);
		}
		ft_printf("--------------------------------------\n");
		ret = SUCCESS;
		sol = lemin->result;
		print_adj_list(sol->graph);
		if (ret == SUCCESS)
		{
			bfs(sol);
			if ((ret = store_valid_path_and_reset(sol)) == FAILURE)
				handle_link_used_both_way(lemin);
		}
		while (lemin->result->prev != NULL)
			lemin->result = lemin->result->prev;
	}
}
