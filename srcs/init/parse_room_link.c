/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/04/24 16:12:34 by amartinod        ###   ########.fr       */
/*                                         how to know if something has been written in the standard output c                                   */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_node_index(t_st_machine *sm, t_hashnode *src, t_hashnode *dest)
{
	t_graph		*graph;
	size_t		i;

	i = 1;
	graph = sm->lemin->link;
	is_it_special_room(sm, src, dest);
	if (src->opt_index == NOT_SET)
	{
		while (i < graph->size && graph->array[i].head != NULL)
			i++;
		src->opt_index = i;
		if (dest->opt_index == NOT_SET)
			dest->opt_index = i + 1;
	}
	else if (dest->opt_index == NOT_SET)
	{
		while (i < graph->size && graph->array[i].head != NULL)
			i++;
		dest->opt_index = i;
	}
}

static void add_edge_and_nam(t_st_machine *sm, t_hashnode *src, t_hashnode *dst)
{
	int8_t		ret;

	ret = add_edge(sm->lemin->link, src->opt_index, dst->opt_index);
	if (ret == SUCCESS)
		ret = add_vertex_name(sm->lemin->link, src->opt_index, (char*)src->key);
	if (ret == SUCCESS)
		ret = add_vertex_name(sm->lemin->link, dst->opt_index, (char*)dst->key);
	if (ret == FAILURE)
		sm->state = ft_perror_failure(ADD_EDGE_FAILED, __FILE__, __LINE__);
}

static void	add_link_adj_list(t_st_machine *sm, t_vector *nsrc, t_vector *ndest)
{
	t_hashnode	*src;
	t_hashnode	*dest;

	src = hashmap_get(sm->lemin->room, vct_getstr(nsrc));
	dest = hashmap_get(sm->lemin->room, vct_getstr(ndest));
	if (src == NULL || dest == NULL)
	{
		ft_printf("src->name %s and adresse src %p\nsrc->name %s and adresse src %p\n", nsrc->str, src, ndest->str, dest);
		sm->state = ft_perror_failure(ROOM_DONT_EXIST, __FILE__, __LINE__);
	}
	else
	{
		get_node_index(sm, src, dest);
		if (get_link(sm->lemin->link, src->opt_index, dest->opt_index) == NULL)
			add_edge_and_nam(sm, src, dest);
	}
}

static void	add_link(t_st_machine *sm, t_vector *line)
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
			init_adjacency_list(sm);
		if (sm->state != E_ERROR)
			add_link(sm, line);
	}
	else
	{
		ft_perror(WRONG_LINK_FORMAT, __FILE__, __LINE__);
		sm->state = E_ERROR;
	}
	return (ret);
}
