/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/03/03 22:04:06 by amartino         ###   ########.fr       */
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

static t_vector 	*get_room_name(t_st_machine *sm, t_vector *dup)
{
	t_vector	*room;

	room = NULL;
	if (vct_chr(dup, '-') != FAILURE)
		sm->state = E_ERROR;
	else
	{
		room = vct_joinfree(&room, &dup, FIRST);
		vct_addchar(room, '\n');
	}
	return (room);
}


//code un peu moche mais temporaire le temps de trouver la façon d'organiser la data
t_vector 	*get_room(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	t_vector	*dup;
	ssize_t		index;
	int32_t		coord;
	size_t		count;

	count = 2;
	dup = NULL;
	while (count > 0)
	{
		index = vct_chr(line, ' ');
		if (dup != NULL)
			vct_del(&dup);
		dup = vct_ndup(line, index);
		if (count == 2)
			room = get_room_name(sm, dup);
		else if (count == 1)
			coord = get_coord(sm, dup);
		vct_pop_from(line, ((size_t)index + 1), START);
		count--;
	}
	coord = get_coord(sm, line);
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
	else if (vct_chr_count(line, ' ') == 2)
	{
		add_line_to_output(sm, line, ROOM);
		room = get_room(sm, line);
		if (room == NULL)
			sm->state = E_ERROR;
		vct_cat(sm->lemin->room, room);
		vct_del(&room);
	}
	else
	{
		sm->state = E_LINK;
		ret = FALSE;
	}
	return (ret);
}
