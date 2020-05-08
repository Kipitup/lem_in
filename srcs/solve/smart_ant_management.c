/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_ant_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:39:03 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/08 10:12:11 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		rewind_solution(t_lemin *lemin)
{
	if (lemin != NULL && lemin->result != NULL)
	{
		while (lemin->result->prev != NULL)
			lemin->result = lemin->result->prev;
	}
}

static uint8_t	should_it_be_interupted(t_solution *sol)
{
	t_solution	*prev;
	size_t		limit;
	uint8_t		ret;

	ret = FALSE;
	limit = 4;
	while (limit > 0 && sol->prev != NULL)
	{
		prev = sol->prev;
		if (sol->net->nb_of_flow == prev->net->nb_of_flow)
			sol = sol->prev;
		else
			break ;
		limit--;
	}
	if (limit == 0)
		ret = TRUE;
	return (ret);
}

/*
** The program returning TRUE if malloc fail is an expected behaviour. Since
** it will break out of the bfs phase and go to the printing part.A NULL network
** prevent the next function, print_final_output, to operate.
*/
uint8_t			smart_ant_management(t_solution *sol, size_t nb_ants)
{
	uint8_t		ret;

	ret = FALSE;
	if (sol != NULL && sol->net == NULL)
	{
		sol->net = init_and_set_network(sol->path, nb_ants);
//		print_debug_network(sol->net);
		if (sol->net != NULL)
		{
			if (sol->net->nb_of_flow > sol->net->nb_of_usable_flow)
				ret = TRUE;
			else if (nb_ants == 1)
				ret = TRUE;
			else if (should_it_be_interupted(sol) == TRUE)
				ret = TRUE;
		}
		else
		{
			ret = TRUE;
			ft_perror(MALLOC_ERR, __FILE__, __LINE__);
		}
	}
	return (ret);
}
