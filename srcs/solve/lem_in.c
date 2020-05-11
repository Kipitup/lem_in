/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/05/11 09:55:54 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lem_in(t_lemin *lemin)
{
	t_solution	*sol;
	int8_t		ret;

	ret = SUCCESS;
	if (lemin != NULL && lemin->result != NULL)
	{
		while (ret == SUCCESS)
		{
			sol = lemin->result;
			ret = bfs(sol);
			if (ret == SUCCESS)
			{
				if ((store_valid_path_and_reset(sol, &used_multiple)) == FAILURE)
				{
					if (smart_ant_management(sol, lemin->nb_ants) == TRUE)
						break ;
					else
						handle_link_used_both_way(lemin);
				}
			}
			else
				smart_ant_management(sol, lemin->nb_ants);
		}
	}
	else
		error_management(LEMIN_UNITIALIZED);
}
