/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/02/26 21:47:43 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int32_t 	get_coord(t_st_machine *sm, t_vector *line)
{
	char		*str;
	int32_t		coord;
	int64_t		tmp;

	coord = 0;
	if (is_it_all_digit(line) == TRUE)
	{
		str = vct_getstr(line);
		tmp = ft_atol(str);
		if (tmp <= INT_MAX && tmp >= 0 && ft_check_int_len(str) == SUCCESS)
			coord = (int32_t)tmp;
	}
	else
		sm->state = E_ERROR;
	return (coord);
}

t_vector 	*get_room(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	t_vector	*tmp;
	size_t		index;
	int32_t		coord;

	index = vct_chr(line, ' ');
	tmp = vct_ndup(line, index);
	room = NULL;
	if (vct_chr(tmp, '-') != FAILURE)
		sm->state = E_ERROR;
	else
	{
		vct_pushstr(tmp, "room name: ");
		room = vct_joinfree(&room, &tmp, BOTH);
		vct_addchar(room, '\n');
		vct_pop_from(line, (index + 1), START);
	}
	index = vct_chr(line, ' ');
	vct_del(&tmp);
	tmp = vct_ndup(line, index);
	coord = get_coord(sm, tmp);
	vct_pop_from(line, (index + 1), START);
	coord = get_coord(sm, line);

	return (room);
}

uint8_t		room(t_st_machine *sm, t_vector *line)
{
	t_vector	*tmp;
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else
	{
		if (vct_chr_count(line, ' ') == 2)
		{
			tmp = get_room(sm, line);
			if (tmp == NULL)
				sm->state = E_ERROR;
			sm->lemin->room = vct_joinfree(&(sm->lemin->room), &tmp, BOTH);
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
