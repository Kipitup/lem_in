/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:46:37 by amartino          #+#    #+#             */
/*   Updated: 2020/05/11 09:53:33 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	get_nb_of_ants(t_st_machine *sm, t_vector *line)
{
	char		*str;
	size_t		size;
	int64_t		tmp;

	size = 0;
	if (is_it_all_digit(line) == TRUE)
	{
		str = vct_getstr(line);
		tmp = ft_atol(str);
		if (tmp <= INT_MAX && tmp >= 0 && ft_check_int_len(str) == SUCCESS)
			size = (size_t)tmp;
		else
			sm->state = ANT_NOT_INT;
	}
	else
		sm->state = ANT_NOT_INT;
	return (size);
}

/*
** The return (TRUE or FALSE) will determine whether or not the parser should
** read the next line.
*/

uint8_t			ant(t_st_machine *sm, t_vector *line)
{
	uint8_t			ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
	{
		ret = check_for_comment_or_command(sm, line);
		if (ret == FALSE)
			sm->state = ANT_NOT_INT;
	}
	else
	{
		sm->state = E_ROOM;
		sm->lemin->nb_ants = get_nb_of_ants(sm, line);
		add_to_buffer(line->str, line->len, ADD_NEW_LINE);
	}
	return (ret);
}
