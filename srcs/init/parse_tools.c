/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:28:27 by amartino          #+#    #+#             */
/*   Updated: 2020/05/10 12:37:03 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	is_it_special_room(t_st_machine *sm, t_hashnode *src, t_hashnode *dest)
{
	t_graph		*graph;
	char		*start;
	char		*end;

	graph = sm->lemin->link;
	start = vct_getstr(sm->lemin->start);
	end = vct_getstr(sm->lemin->end);
	if (ft_strequ(src->key, start) == TRUE)
		src->opt_index = 0;
	else if (ft_strequ(src->key, end) == TRUE)
		src->opt_index = graph->size - 1;
	if (ft_strequ(dest->key, start) == TRUE)
		dest->opt_index = 0;
	else if (ft_strequ(dest->key, end) == TRUE)
		dest->opt_index = graph->size - 1;
}

uint8_t	is_it_all_digit(t_vector *line)
{
	size_t		i;
	size_t		len;
	int8_t		ret;

	i = (vct_getchar_at(line, 0) == '-') ? 1 : 0;
	len = vct_len(line);
	if (len == 0)
		return (FALSE);
	while (i < len)
	{
		ret = ft_isdigit(vct_getchar_at(line, i));
		if (ret == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

uint8_t	check_for_comment_or_command(t_st_machine *sm, t_vector *line)
{
	uint8_t	ret;

	ret = TRUE;
	if (vct_chr_str(line, "##") == START)
	{
		sm->state = E_COMMAND;
		ret = FALSE;
	}
	else
		add_to_buffer(line->str, line->len, ADD_NEW_LINE);
	return (ret);
}
