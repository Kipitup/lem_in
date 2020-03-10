/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/03/09 20:16:46 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	does_room_exist(t_st_machine *sm, t_vector *room)
{
//	t_hashnode	*node;
//
//	node = hashmap_get(sm->room, vct_getstr(room));
//	if (node == NULL)
//	{
//		ft_perror(ROOM_DONT_EXIST, __FILE__, __LINE__);
//		return (E_ERROR);
//	}
	return (E_LINK);
}

static void		get_link(t_st_machine *sm, t_vector *line)
{
	t_vector	*room;
	size_t		index;
	int8_t		ret;

	index = vct_chr(line, '-');
	room = vct_ndup(line, index);
	sm->state = does_room_exist(sm, room);
	if (sm->state != E_ERROR)
	{
	//	ret = add_edge(sm->link, 
	}
	vct_del(&dup);
}

static void		init_adjacency_list(t_st_machine *sm, size_t size)
{
	sm->link = init_graph(size);
	if (sm->link == NULL)
	{
		ft_perror(ADJ_LIST_MALLOC, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
}

/*
 **	The return (TRUE or FALSE) will determine whether or not the parser should
 **	read the next line.
 */
uint8_t			room_link(t_st_machine *sm, t_vector *line)
{
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, '-') == 1)
	{
		add_line_to_output(sm, line, ROOM_LINK);
		if (sm->link == NULL)
			init_adjacency_list(sm, 6); //replace by hashmap->nb_ol_elem
		if (sm->state != E_ERROR)
			get_link(sm, line);
	}
	else
	{
		ft_perror(WRONG_LINK_FORMAT, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	return (ret);
}
