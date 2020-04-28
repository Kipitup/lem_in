/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/28 16:43:18 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_in(t_lemin *lemin)
{
	t_solution	*sol;
	int8_t		ret;

	ret = SUCCESS;
	if (lemin != NULL && lemin->result != NULL)
	{
//		print_link_available(lemin->link->array[0]);
//		print_link_available(lemin->link->array[lemin->link->size - 1]);
		while (ret == SUCCESS)
		{
			sol = lemin->result;
			ret = bfs(sol);
			if (ret == SUCCESS)
			{
				if ((store_valid_path_and_reset(sol)) == FAILURE)
					handle_link_used_both_way(lemin);
//				print_all_path(sol->path);//print only the paths' len. more readable
//				usleep(700000);
			}
		}
	}
	else
		ft_perror(LEMIN_UNITIALIZED, __FILE__, __LINE__);
}
