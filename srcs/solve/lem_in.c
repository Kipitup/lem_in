/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/05/11 10:16:09 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static uint8_t	store_path_handle_link(t_solution *sol, t_lemin *lemin,
		size_t used_multiple)
{
	uint8_t	ret;

	ret = FALSE;
	if ((store_valid_path_and_reset(sol, &used_multiple)) == FAILURE)
	{
		if (smart_ant_management(sol, lemin->nb_ants) == TRUE)
			ret = TRUE;
		else
			handle_link_used_both_way(lemin);
	}
	return (ret);
}

void			lem_in(t_lemin *lemin)
{
	t_solution	*sol;
	size_t		used_multiple;
	int8_t		ret;

	ret = SUCCESS;
	used_multiple = 0;
	if (lemin != NULL && lemin->result != NULL)
	{
		while (ret == SUCCESS)
		{
			sol = lemin->result;
			ret = bfs(sol);
			if (ret == SUCCESS)
			{
				if (store_path_handle_link(sol, lemin, used_multiple) == TRUE)
					break ;
			}
			else
				smart_ant_management(sol, lemin->nb_ants);
		}
	}
	else
		error_management(LEMIN_UNITIALIZED);
}
