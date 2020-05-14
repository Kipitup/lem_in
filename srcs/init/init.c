/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/05/14 17:10:49 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				init_adjacency_list(t_st_machine *sm)
{
	size_t	size;

	size = sm->lemin->room->nb_of_elem;
	if (size == 0)
		sm->state = NO_ROOM;
	else if (sm->lemin->start == NULL)
		sm->state = NO_START;
	else if (sm->lemin->end == NULL)
		sm->state = NO_END;
	else
	{
		sm->lemin->link = init_graph(size);
		if (sm->lemin->link == NULL && sm->lemin->result->graph)
			sm->state = ADJ_LIST_MALLOC;
	}
}

static void			last_quick_check(t_st_machine *sm)
{
//	[?] need a way to protect this without the output and write a \n if it succeed
//	if (sm->lemin->output->len == 0)
//		sm->state = EMPTY_FILE;
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
		{
			lemin = sm->lemin;
			init_solution(lemin); //[?] need to check if SUCCESS
			if (VISU == TRUE)
				init_file_for_visu(lemin->link, NULL);
			add_to_buffer("\n", 1, ADD_NO_NEW_LINE);
		}
		else
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
