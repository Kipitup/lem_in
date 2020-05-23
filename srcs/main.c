/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/05/21 22:25:36 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin	*lemin;
	int		ret;

	ret = FAILURE;
	lemin = init();
	if (lemin != NULL)
	{
		lem_in(lemin);
		rewind_solution(lemin);
		ret = print_final_output(lemin);
	}
	clean_lemin(&lemin);
	return (ret);
}

/*
** __attribute__((destructor))void	dest_end()
** {
** 	ft_printf("coucou\n");
** 	while(1);
** }
*/
