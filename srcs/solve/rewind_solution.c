/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewind_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 12:43:43 by francis           #+#    #+#             */
/*   Updated: 2020/04/21 12:45:20 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	rewind_solution(t_lemin *lemin)
{
	if (lemin != NULL && lemin->result != NULL)
	{
		while (lemin->result->prev != NULL)
			lemin->result = lemin->result->prev;
	}
}
