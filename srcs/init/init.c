/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/03/09 18:37:49 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_lemin			*init_struct_lemin(void)
{
	t_lemin		*lemin;

	lemin = ft_memalloc(sizeof(t_lemin));
	if (lemin != NULL)
	{
		lemin->output = vct_new(DEFAULT_VCT_SIZE);
		lemin->room = hashmap_create(NULL, NULL);//compare , free function
		lemin->link = vct_new(DEFAULT_VCT_SIZE);
		if (lemin->output == NULL || lemin->room == NULL || lemin->link == NULL)
			clean_lemin(&(lemin));
	}
	return (lemin);
}

static t_st_machine		*init_struct(void)
{
	t_st_machine *sm;

	sm = ft_memalloc(sizeof(t_st_machine));
	if (sm != NULL)
	{
		sm->state = E_ANT;
		sm->lemin = init_struct_lemin();
		if (sm->lemin == NULL)
			clean_state_machine(&sm);
	}
	return (sm);
}

t_lemin					*init(void)
{
	t_lemin			*lemin;
	t_st_machine	*sm;

	lemin = NULL;
	sm = init_struct();
	if (sm != NULL)
	{
		parse(sm);
		if (sm->state != E_ERROR)
			lemin = sm->lemin;
		else
			clean_lemin(&(sm->lemin));
		clean_state_machine(&sm);
	}
	return (lemin);
}
