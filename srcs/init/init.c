/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/05/19 09:55:46 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			last_quick_check(t_st_machine *sm)
{
	if (sm->lemin->link != NULL)
	{
		if (sm->lemin->link->array[0].head == NULL)
			sm->state = NO_LINK_TO_START;
		else if (sm->lemin->link->array[sm->lemin->link->size - 1].head == NULL)
			sm->state = NO_LINK_TO_END;
	}
	else
		sm->state = NO_VALID_LINK;
}

static t_lemin		*init_struct_lemin(void)
{
	t_lemin		*lemin;

	lemin = ft_memalloc(sizeof(t_lemin));
	if (lemin != NULL)
	{
		lemin->room = hashmap_create(NULL, NULL);
		if (lemin->room == NULL)
			clean_lemin(&(lemin));
	}
	return (lemin);
}

static t_st_machine	*init_struct(void)
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

static void			assign_sm_to_lemin_and_sol(t_lemin **lemin,
		t_st_machine **sm)
{
	*lemin = (*sm)->lemin;
	init_solution(*lemin);
	if ((*lemin)->result == NULL)
		(*sm)->state = E_ERROR;
	if (VISU == TRUE)
		init_file_for_visu((*lemin)->link, NULL);
	add_to_buffer("\n", 1, ADD_NO_NEW_LINE);
}

t_lemin				*init(void)
{
	t_lemin			*lemin;
	t_st_machine	*sm;

	lemin = NULL;
	sm = init_struct();
	if (sm != NULL)
	{
		parse(sm);
		if (sm->state > E_ERROR || sm->state < ERR_STOP_LEMIN)
			last_quick_check(sm);
		if (sm->state > E_ERROR || sm->state < ERR_STOP_LEMIN)
			assign_sm_to_lemin_and_sol(&lemin, &sm);
		if (sm->state <= E_ERROR && sm->state >= ERR_STOP_LEMIN)
		{
			error_management(sm->state);
			clean_lemin(&(sm->lemin));
		}
		clean_state_machine(&sm);
	}
	else
		error_management(LEMIN_UNITIALIZED);
	return (lemin);
}
