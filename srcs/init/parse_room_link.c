/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/03/11 14:53:08 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_node_index(t_st_machine *sm, t_hashnode *src, t_hashnode *dest)
{
	t_graph		*graph;
	size_t		i;

	i = 1;
	graph = sm->lemin->link;
	is_it_special_room(sm, src, dest);
	if (src->index == NOT_SET)
	{
		while (i < graph->size && graph->array[i].head != NULL) 
			i++;
		src->index = i;
		if (dest->index == NOT_SET)
			dest->index = i + 1;
	}
	else if (dest->index == NOT_SET)
	{
		while (i < graph->size && graph->array[i].head != NULL) 
			i++;
		dest->index = i;
	}
}

static void	add_link_adj_list(t_st_machine *sm, t_vector *src, t_vector *dest)
{
	t_hashnode	*node_src;
	t_hashnode	*node_dest;
	int8_t		ret;

	ret = SUCCESS;
	node_src = hashmap_get(sm->lemin->room, vct_getstr(src));
	node_dest = hashmap_get(sm->lemin->room, vct_getstr(dest));
	if (node_src == NULL || node_dest == NULL)
	{
		ft_perror(ROOM_DONT_EXIST, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	else
	{
		get_node_index(sm, node_src, node_dest);
		if (does_link_exist(sm->lemin->link, node_src->index,
					node_dest->index) == FALSE)
		{
			ret = add_edge(sm->lemin->link, node_src->index, node_dest->index);
		}
		if (ret == FAILURE)
			sm->state = E_ERROR;
	}
}

static void	get_link(t_st_machine *sm, t_vector *line)
{
	t_vector	*src;
	t_vector	*dest;
	size_t		index;

	index = vct_chr(line, '-');
	src = vct_ndup(line, index);
	dest = vct_dup_from(line, (index + 1));
	if (src != NULL && dest != NULL)
		add_link_adj_list(sm, src, dest);
	else
	{
		ft_perror(VECTOR_FAIL, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	vct_del(&src);
	vct_del(&dest);
}

/*
 **	The return (TRUE or FALSE) will determine whether or not the parser should
 **	read the next line.
 */
uint8_t		room_link(t_st_machine *sm, t_vector *line)
{
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, '-') == 1)
	{
		add_line_to_output(sm, line, ROOM_LINK);
		if (sm->lemin->link == NULL)
			init_adjacency_list(sm); //replace by hashmap->nb_ol_elem
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
