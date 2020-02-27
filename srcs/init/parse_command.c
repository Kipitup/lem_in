/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/02/27 16:50:15 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	next_room_is_special(t_st_machine *sm, t_vector *line, uint8_t type)
{
	t_vector	*tmp;
	int8_t		ret;

	(void)type;
	tmp = NULL;
	add_line_to_output(sm, line, COMMAND);
	ret = vct_read_line(STD_IN, &tmp);
	if (ret <= 0)
		sm->state = E_ERROR;
	else
		add_line_to_output(sm, tmp, SPECIAL_ROOM);
	vct_del(&tmp);
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
