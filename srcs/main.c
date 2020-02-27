/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/02/27 13:36:39 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		*lemin;

	lemin = init();
	if (lemin != NULL)
	{
		vct_print(lemin->output);
		ft_printf("\n\nNB OF ANTS: %zu\nRoom: \n%s\n", lemin->nb_ants, lemin->room->str);
	}
	else
		ft_printf("error\n");
	clean_lemin(&lemin);
	return (SUCCESS);
}

// __attribute__((destructor))void	dest_end()
// {
// 	ft_printf("coucou\n");
// 	while(1);
// }
