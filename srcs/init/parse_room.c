/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/02/28 14:17:30 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int32_t 	get_coord(t_st_machine *sm, t_vector *line)
{
	char		*str;
	int32_t		coord;
	int64_t		tmp;

	coord = 0;
	if (is_it_all_digit(line) == TRUE)
	{
		str = vct_getstr(line);
		tmp = ft_atol(str);
		if (tmp > INT_MAX || tmp < INT_MIN || ft_check_int_len(str) == FAILURE)
			sm->state = E_ERROR;
		else
			coord = (int32_t)tmp;
	}
	else
		sm->state = E_ERROR;
	return (coord);
}

static t_vector 	*get_room_name(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	t_vector	*dup;
	size_t		index;

	room = NULL;
	index = vct_chr(line, ' ');
	dup = vct_ndup(line, index);
	if (vct_chr(dup, '-') != FAILURE)
		sm->state = E_ERROR;
	else
	{
		vct_pushstr(dup, "\troom name: ");
		room = vct_joinfree(&room, &dup, FIRST);
		vct_addchar(room, '\n');
		vct_pop_from(line, (index + 1), START);
	}
	vct_del(&dup);
	return (room);
}


//code très moche mais temporaire le temps de trouver la façon d'organiser la data
static t_vector 	*get_room(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	t_vector	*dup;
	t_vector	*dup2;
	size_t		index;
	int32_t		coord;

	room = NULL;
	dup = vct_dup(line);
	if (dup != NULL)
	{
		room = get_room_name(sm, dup);

		index = vct_chr(dup, ' ');
		dup2 = vct_ndup(dup, index);
		coord = get_coord(sm, dup2);
		// ft_printf("coord %d\t", coord);
		vct_pop_from(dup, (index + 1), START);
		coord = get_coord(sm, dup);
		// ft_printf("coord2 %d\n", coor);
		vct_del(&dup2);
	}
	vct_del(&dup);
	return (room);
}

uint8_t		room(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else
	{
		if (vct_chr_count(line, ' ') == 2)
		{
			room = get_room(sm, line);
			if (room == NULL)
				sm->state = E_ERROR;
			sm->lemin->room = vct_joinfree(&(sm->lemin->room), &room, BOTH);
			add_line_to_output(sm, line, ROOM);
		}
		else
		{
			sm->state = E_LINK;
			ret = FALSE;
		}
	}
	return (ret);
}
