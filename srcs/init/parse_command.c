/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/02/26 18:49:48 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	next_room_is_special(t_st_machine *sm, t_vector *line, uint8_t type)
{
	int8_t					ret;

	(void)type;
	add_line_to_output(sm, line, COMMAND);
	vct_del(&line);
	ret = vct_read_line(STD_IN, &line);
	if (ret <= 0)
		sm->state = E_ERROR;
	else
		add_line_to_output(sm, line, SPECIAL_ROOM);
}

uint8_t		command(t_st_machine *sm, t_vector *line)
{
	if (vct_strequ(line, "##start") == TRUE)
		next_room_is_special(sm, line, START);
	else if (vct_strequ(line, "##end") == TRUE)
		next_room_is_special(sm, line, END);
	else
		add_line_to_output(sm, line, COMMAND);
	sm->state = E_ROOM;
	return (TRUE);
}
