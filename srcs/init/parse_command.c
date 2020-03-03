/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/03/03 15:59:47 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vector 	*get_special_room(t_st_machine *sm, t_vector *room, t_vector *tmp)
{
	if (room != NULL)
		sm->state = E_ERROR;
	else if (vct_chr_count(tmp, ' ') == 2)
	{
		room = get_room(sm, tmp);
		if (room == NULL)
			sm->state = E_ERROR;
		sm->lemin->room = vct_joinfree(&(sm->lemin->room), &room, FIRST);
	}
	else
		sm->state = E_ERROR;
	return (room);
}

void	next_room_is_special(t_st_machine *sm, uint8_t type)
{
	t_vector	*tmp;
	int8_t		ret;

	tmp = NULL;
	ret = vct_read_line(STD_IN, &tmp);
	if (ret <= 0)
		sm->state = E_ERROR;
	else
	{
		add_line_to_output(sm, tmp, SPECIAL_ROOM);
		if (type == START)
			sm->lemin->start = get_special_room(sm, sm->lemin->start, tmp);
		else
			sm->lemin->end = get_special_room(sm, sm->lemin->end, tmp);
	}
	vct_del(&tmp);
}

uint8_t		command(t_st_machine *sm, t_vector *line)
{
	sm->state = E_ROOM;
	add_line_to_output(sm, line, COMMAND);
	if (vct_strequ(line, "##start") == TRUE)
		next_room_is_special(sm, START);
	else if (vct_strequ(line, "##end") == TRUE)
		next_room_is_special(sm, END);
	return (TRUE);
}
