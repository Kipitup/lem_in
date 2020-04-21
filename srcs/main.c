/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/04/17 16:21:12 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		*lemin;

	lemin = init();
	if (lemin != NULL)
	{
		lem_in(lemin);
		rewind_solution(lemin);
		print_all_path(lemin);
		//        print_final_output(lemin);
	}
	else
		ft_dprintf(STD_ERR, "error\n");
	clean_lemin(&lemin);
	// need to free all of sol list when its over
	return (SUCCESS);
}

// __attribute__((destructor))void	dest_end()
// {
// 	ft_printf("coucou\n");
// 	while(1);
// }
