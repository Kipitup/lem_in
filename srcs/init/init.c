/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/04/22 17:30:10 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				init_adjacency_list(t_st_machine *sm)
{
	size_t	size;

	size = sm->lemin->room->nb_of_elem;
	sm->lemin->link = init_graph(size);
	if (sm->lemin->link == NULL && sm->lemin->result->graph)
	{
		ft_perror(ADJ_LIST_MALLOC, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
}

static void			last_quick_check(t_st_machine *sm)
{
	if (sm->lemin->output->len == 0)
		sm->state = ft_perror_failure(EMPTY_FILE, __FILE__, __LINE__);
	if (sm->lemin->start == NULL)
		sm->state = ft_perror_failure(NO_START, __FILE__, __LINE__);
	if (sm->lemin->end == NULL)
		sm->state = ft_perror_failure(NO_END, __FILE__, __LINE__);
	if (sm->lemin->link != NULL)
	{
		if (sm->lemin->link->array[0].head == NULL)
			sm->state = ft_perror_failure(NO_LINK_TO_START, __FILE__, __LINE__);
		if (sm->lemin->link->array[sm->lemin->link->size - 1].head == NULL)
			sm->state = ft_perror_failure(NO_LINK_TO_END, __FILE__, __LINE__);
	}
}

static t_lemin		*init_struct_lemin(void)
{
	t_lemin		*lemin;

	lemin = ft_memalloc(sizeof(t_lemin));
	if (lemin != NULL)
	{
		lemin->output = vct_new(DEFAULT_VCT_SIZE);
		lemin->room = hashmap_create(NULL, NULL);
		if (lemin->output == NULL || lemin->room == NULL)
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
	t_lemin		*lemin;
	t_st_machine	*sm;

	lemin = NULL;
	sm = init_struct();
	if (sm != NULL)
	{
		parse(sm);
		if (sm->state != E_ERROR)
			last_quick_check(sm);
		if (sm->state != E_ERROR)
			lemin = sm->lemin;
		else
			clean_lemin(&(sm->lemin));
		init_solution(lemin);
		clean_state_machine(&sm);
	}
	return (lemin);
}
