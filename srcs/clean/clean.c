/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:45:44 by amartino          #+#    #+#             */
/*   Updated: 2020/03/10 16:27:30 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_lemin(t_lemin **lemin)
{
	if (lemin != NULL && *lemin != NULL)
	{
		vct_del(&((*lemin)->output));
		del_map(&((*lemin)->room));
		clean_graph(&((*lemin)->link));
		vct_del(&((*lemin)->start));
		vct_del(&((*lemin)->end));
		ft_memdel((void**)lemin);
	}
}

void	clean_state_machine(t_st_machine **sm)
{
	if (sm != NULL && *sm != NULL)
		ft_memdel((void**)sm);
}
