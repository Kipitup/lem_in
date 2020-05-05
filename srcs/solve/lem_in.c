/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:47:02 by amartino          #+#    #+#             */
/*   Updated: 2020/05/05 11:39:51 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_in(t_lemin *lemin)
{
	t_solution	*sol;
	int8_t		ret;
	size_t		count_bfs = 0;
	size_t		new_sequence = 0;
	size_t		used_multiple = 0;

	ret = SUCCESS;
	if (lemin != NULL && lemin->result != NULL)
	{
		while (ret == SUCCESS)
		{
			sol = lemin->result;
			count_bfs++;
			ret = bfs(sol);
			if (ret == SUCCESS)
			{
//			[!] if malloc fail in func below what happen, need to stop the program..
				if ((store_valid_path_and_reset(sol, &used_multiple)) == FAILURE)
				{
					new_sequence++;
			ft_dprintf(STD_ERR, "BFS exploration: {c_cyan}%zu{c_end}\n", count_bfs);
			print_all_path_len(sol->path);
					handle_link_used_both_way(lemin);
				}
			}
		}
		ft_dprintf(STD_ERR, "BFS exploration: {c_red}%zu{c_end}\n", count_bfs);
		ft_dprintf(STD_ERR, "New sequence:    {c_red}%zu{c_end}\n", new_sequence);
		ft_dprintf(STD_ERR, "Used multiple:   {c_red}%zu{c_end}\n", used_multiple);
	}
	else
		ft_perror(LEMIN_UNITIALIZED, __FILE__, __LINE__);
}
