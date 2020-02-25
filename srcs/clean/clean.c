/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:45:44 by amartino          #+#    #+#             */
/*   Updated: 2020/02/25 19:47:54 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clean_lemin(t_lemin **lemin)
{
	if (lemin != NULL && *lemin != NULL)
	{
		vct_del(&((*lemin)->output_text));
		ft_memdel((void**)lemin);
	}
}

void	clean_state_machine(t_st_machine **sm)
{
	if (sm != NULL && *sm != NULL)
		ft_memdel((void**)sm);
}
