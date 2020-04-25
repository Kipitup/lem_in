/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/04/25 08:38:58 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vector		*getspecial_room(t_st_machine *sm, t_vector *room,
										t_vector *line)
{
	size_t	index;

	if (room != NULL)
		sm->state = ft_perror_failure(MANY_START_OR_END, __FILE__, __LINE__);
	else if (vct_chr_count(line, ' ') == 2 && vct_getchar_at(line, 0) != '#')
	{
		if (get_room(sm, line) != FAILURE)
		{
			index = vct_chr(line, ' ');
			room = vct_ndup(line, index);
			if (room == NULL)
				sm->state = ft_perror_failure(MALLOC_ERR, __FILE__, __LINE__);
		}
	}
	else
		sm->state = ft_perror_failure(NO_ROOM_AFTER_CMD, __FILE__, __LINE__);
	return (room);
}

static void			next_room_is_special(t_st_machine *sm, uint8_t type)
{
	t_vector	*new_line;
	int8_t		ret;

	new_line = NULL;
	ret = vct_read_line(STD_IN, &new_line);
	if (ret < 0)
		sm->state = ft_perror_failure(READ_LINE_ERR, __FILE__, __LINE__);
	else
	{
		add_line_to_output(sm, new_line, SPECIAL_ROOM);
		if (type == START)
			sm->lemin->start = getspecial_room(sm, sm->lemin->start, new_line);
		else
			sm->lemin->end = getspecial_room(sm, sm->lemin->end, new_line);
	}
	vct_del(&new_line);
}

/*
** The return (TRUE or FALSE) will determine whether or not the parser should
** read the next line.
*/

uint8_t				command(t_st_machine *sm, t_vector *line)
{
	sm->state = E_ROOM;
	add_line_to_output(sm, line, COMMAND);
	if (vct_strequ(line, "##start") == TRUE)
		next_room_is_special(sm, START);
	else if (vct_strequ(line, "##end") == TRUE)
		next_room_is_special(sm, END);
	return (TRUE);
}
