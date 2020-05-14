/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:50:12 by amartino          #+#    #+#             */
/*   Updated: 2020/05/14 15:45:21 by amartinod        ###   ########.fr       */
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
			sm->state = COORD_NOT_INT;
	}
	else
		sm->state = COORD_NOT_INT;
	return (coord);
}

static t_vector	*get_room_name(t_st_machine *sm, t_vector *dup)
{
	ssize_t		chr;
	char		c;

	chr = vct_chr(dup, '-');
	if (chr > FAILURE)
		sm->state = DASH_IN_ROOM_NAME;
	c = vct_getchar_at(dup, START);
	if (c == 'L')
		sm->state = ROOM_START_WITH_L;
	return (dup);
}

static void		add_room_to_hashmap(t_st_machine *sm, char *key, char *coord)
{
	t_hashnode	*node;
	int8_t		ret;

	if (key != NULL && coord != NULL)
	{
		node = hashmap_get(sm->lemin->room, key);
		if (node == NULL)
		{
			ret = hashmap_set(sm->lemin->room, key, coord);
			if (ret == FAILURE)
				sm->state = MALLOC_ERR;
		}
		else
		{
			ft_strdel(&key);
			ft_strdel(&coord);
			sm->state = ROOM_DUPLICATE;
		}
	}
	else
		sm->state = MALLOC_ERR;
}

void			get_room(t_st_machine *sm, t_vector *line)
{
	t_vector	**tab_vct;
	t_vector	*key;
	t_vector	*coord;
	t_vector	*coord2;

	tab_vct = vct_split(line, ' ');
	if (tab_vct != NULL)
	{
		key = get_room_name(sm, tab_vct[0]);
		coord = get_coord(sm, tab_vct[1]);
		vct_addchar(coord, ' ');
		coord2 = get_coord(sm, tab_vct[2]);
		if (vct_cat(coord, coord2) == FAILURE)
			sm->state = MALLOC_ERR;
		if (sm->state > E_ERROR)
			add_room_to_hashmap(sm, ft_strdup(key->str), ft_strdup(coord->str));
		vct_del_tab(&tab_vct);
	}
	else
		sm->state = MALLOC_ERR;
}

/*
** The return (TRUE or FALSE) will determine whether or not the parser should
** read the next line.
*/

uint8_t			room(t_st_machine *sm, t_vector *line)
{
	uint8_t		ret;

	ret = FALSE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, ' ') == 2)
	{
		if (vct_apply(line, IS_PRINT) == FALSE)
			sm->state = NO_PRINTABLE_CHAR;
		else
		{
			add_to_buffer(line->str, line->len, ADD_NEW_LINE);
			get_room(sm, line);
			ret = TRUE;
		}
	}
	else
		sm->state = E_LINK;
	return (ret);
}
