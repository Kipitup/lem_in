/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/17 17:32:21 by amartinod        ###   ########.fr       */
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
				else
				{
					if (check_vertex_used(sol) == TRUE)
						update_links(sol);
				}
			}
		}
	}//protect if lemin == NULL || lemin->result == NULL
}
