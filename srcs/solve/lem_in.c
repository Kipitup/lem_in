/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/05/02 10:51:13 by francis          ###   ########.fr       */
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
				vertex_used_more(sol->graph);
				if ((store_valid_path_and_reset(sol)) == FAILURE)
				{
					ft_printf("{c_cyan}New Sequence{c_end}\n");
					handle_link_used_both_way(lemin);
				}
//				print_all_path(sol->path);//print only the paths' len. more readable
//				usleep(700000);
			}
		}
	}
	else
		ft_perror(LEMIN_UNITIALIZED, __FILE__, __LINE__);
}
