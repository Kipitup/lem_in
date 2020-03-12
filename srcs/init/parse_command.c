/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:48:36 by amartino          #+#    #+#             */
/*   Updated: 2020/03/12 14:19:38 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vector		*get_name_and_coord(t_st_machine *sm, t_vector *line)
{
	t_vector	**tab_vct;
	t_vector	*key;
	t_vector	*crd;

	tab_vct = vct_split(line, ' ');
	key = get_room_name(sm, tab_vct[0]);
	crd = get_coord(sm, tab_vct[1]);
	get_second_coord(sm, crd, tab_vct[2]);
	if (sm->state != E_ERROR)
		hashmap_set(sm->lemin->room, ft_strdup(key->str), ft_strdup(crd->str));
	vct_del_tab(&tab_vct);
	return (key);
}

static t_vector		*getspecial_room(t_st_machine *sm, t_vector *room,
										t_vector *new_line)
{
	if (room != NULL)
		sm->state = E_ERROR;
	else if (vct_chr_count(new_line, ' ') == 2)
	{
		room = get_name_and_coord(sm, new_line);
		if (room == NULL)
			sm->state = E_ERROR;
	}
	else
		sm->state = E_ERROR;
	return (room);
}

static void			next_room_is_special(t_st_machine *sm, uint8_t type)
{
	t_vector	*new_line;
	int8_t		ret;

	new_line = NULL;
	ret = vct_read_line(STD_IN, &new_line);
	if (ret <= 0)
		sm->state = E_ERROR;
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
