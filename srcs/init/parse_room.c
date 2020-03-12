/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/03/12 11:18:17 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		get_second_coord(t_vector *coord, char *second_coord)
{
	vct_addchar(coord, ' ');
	vct_addstr(coord, second_coord);
}

char		*get_coord(t_st_machine *sm, t_vector *line)
{
	char		*str;
	int64_t		tmp;

	str = NULL;
	if (is_it_all_digit(line) == TRUE)
	{
		str = vct_getstr(line);
		tmp = ft_atol(str);
		if (tmp > INT_MAX || tmp < INT_MIN || ft_check_int_len(str) == FAILURE)
			sm->state = E_ERROR;
	}
	else
		sm->state = E_ERROR;
	return (str);
}

t_vector 	*get_room_name(t_st_machine *sm, t_vector *dup)
{
	t_vector	*room;

	room = NULL;
	if (vct_chr(dup, '-') != FAILURE)
	{
		ft_perror(DASH_IN_ROOM_NAME, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	else
		room = vct_dup(dup);
	return (room);
}

//code un peu moche mais temporaire le temps de trouver la façon d'organiser la data
int8_t 		get_room(t_st_machine *sm, t_vector *line)
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
	if (sm->state != E_ERROR)
		hashmap_set(sm->lemin->room, ft_strdup(key->str), ft_strdup(coord->str));
	vct_del(&key);
	vct_del(&coord);
	return (TRUE);
}

/*
** The return (TRUE or FALSE) will determine whether or not the parser should
** read the next line.
*/
uint8_t		room(t_st_machine *sm, t_vector *line)
{
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, ' ') == 2)
	{
		add_line_to_output(sm, line, ROOM);
		ret = get_room(sm, line);	
		if (ret == FALSE)
			sm->state = E_ERROR;
	}
	else
	{
		sm->state = E_LINK;
		ret = FALSE;
	}
	return (ret);
}
