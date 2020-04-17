/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/16 15:15:30 by francis          ###   ########.fr       */
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
		print_adj_list(lemin->link);
		while (ret == SUCCESS)
		{
			sol = lemin->result;
			if ((ret = bfs(sol)) == SUCCESS)
			{
				if ((store_valid_path_and_reset(sol)) == FAILURE)
					handle_link_used_both_way(lemin);
			}
		}
	}
	while (lemin->result->prev != NULL)
		lemin->result = lemin->result->prev;
}
