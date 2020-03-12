/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/03/12 14:21:51 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		get_second_coord(t_st_machine *sm, t_vector *coord,
								t_vector *second_coord)
{
	char		*str;
	int64_t		tmp;

	str = vct_getstr(second_coord);
	if (is_it_all_digit(second_coord) == TRUE)
	{
		tmp = ft_atol(str);
		if (tmp > INT_MAX || tmp < INT_MIN || ft_check_int_len(str) == FAILURE)
			sm->state = E_ERROR;
		vct_addchar(coord, ' ');
		vct_cat(coord, second_coord);
	}
	else
		sm->state = E_ERROR;
}

t_vector	*get_coord(t_st_machine *sm, t_vector *dup)
{
	char		*str;
	int64_t		tmp;

	str = vct_getstr(dup);
	if (is_it_all_digit(dup) == TRUE)
	{
		tmp = ft_atol(str);
		if (tmp > INT_MAX || tmp < INT_MIN || ft_check_int_len(str) == FAILURE)
			sm->state = E_ERROR;
	}
	else
		sm->state = E_ERROR;
	return (dup);
}

t_vector	*get_room_name(t_st_machine *sm, t_vector *dup)
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

int8_t		get_room(t_st_machine *sm, t_vector *line)
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
	vct_del(&key);
	vct_del_tab(&tab_vct);
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
