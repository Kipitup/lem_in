/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/04/09 09:28:38 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_vector	*get_coord(t_st_machine *sm, t_vector *coord)
{
	char		*str;
	int64_t		tmp;

	str = vct_getstr(coord);
	if (is_it_all_digit(coord) == TRUE)
	{
		tmp = ft_atol(str);
		if (tmp > INT_MAX || tmp < INT_MIN || ft_check_int_len(str) == FAILURE)
			sm->state = ft_perror_failure(COORD_NOT_INT, __FILE__, __LINE__);
	}
	else
		sm->state = ft_perror_failure(COORD_NOT_INT, __FILE__, __LINE__);
	return (coord);
}

static t_vector	*get_room_name(t_st_machine *sm, t_vector *dup)
{
	t_vector	*room;

	room = NULL;
	if (vct_chr(dup, '-') != FAILURE)
	{
		ft_perror(DASH_IN_ROOM_NAME, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	else if (vct_getchar_at(dup, START) == 'L')
	{
		ft_perror(ROOM_START_WITH_L, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	return (dup);
}

int8_t			get_room(t_st_machine *sm, t_vector *line)
{
	t_vector	**tab_vct;
	t_vector	*key;
	t_vector	*coord;
	t_vector	*coord2;
	int8_t		ret;

	ret = FAILURE;
	tab_vct = vct_split(line, ' ');
	if (tab_vct != NULL)
	{
		key = get_room_name(sm, tab_vct[0]);
		coord = get_coord(sm, tab_vct[1]);
		vct_addchar(coord, ' ');
		coord2 = get_coord(sm, tab_vct[2]);
		if (vct_cat(coord, coord2) == FAILURE)
			sm->state = ft_perror_failure(MALLOC_ERR, __FILE__, __LINE__);
		if (sm->state != E_ERROR)
			ret = hashmap_set(sm->lemin->room, ft_strdup(key->str),
					ft_strdup(coord->str));
		vct_del_tab(&tab_vct);
	}
	else
		sm->state = ft_perror_failure(MALLOC_ERR, __FILE__, __LINE__);
	return (ret);
}

/*
** The return (TRUE or FALSE) will determine whether or not the parser should
** read the next line.
*/
uint8_t			room(t_st_machine *sm, t_vector *line)
{
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, ' ') == 2)
	{
		add_line_to_output(sm, line, ROOM);
		get_room(sm, line);
		if (sm->state == E_ERROR)
			ret = FALSE;
	}
	else
	{
		sm->state = E_LINK;
		ret = FALSE;
	}
	return (ret);
}
