/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/03/10 15:18:01 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vector		*get_name_n_coord(t_st_machine *sm, t_vector *line)
{
	t_vector	*key;
	t_vector	*coord;
	t_vector	*dup;
	ssize_t		index;
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
			key = get_room_name(sm, dup);
		else if (count == 1)
			coord = vct_newstr(get_coord(sm, dup));
		vct_pop_from(line, ((size_t)index + 1), START);
		count--;
	}
	get_second_coord(coord, get_coord(sm, line));
	vct_del(&dup);
	hashmap_set(sm->lemin->room, key->str, coord->str);
	return (key);
}

static t_vector 	*getspecial_room(t_st_machine *sm, t_vector *room, t_vector *tmp)
{
	if (room != NULL)
		sm->state = E_ERROR;
	else if (vct_chr_count(tmp, ' ') == 2)
	{
		room = get_name_n_coord(sm, tmp);
		if (room == NULL)
			sm->state = E_ERROR;
	}
	else
		sm->state = E_ERROR;
	return (room);
}

static void	next_room_is_special(t_st_machine *sm, uint8_t type)
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
			sm->lemin->start = getspecial_room(sm, sm->lemin->start, tmp);
		else
			sm->lemin->end = getspecial_room(sm, sm->lemin->end, tmp);
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
