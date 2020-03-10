/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ant.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 18:46:37 by amartino          #+#    #+#             */
/*   Updated: 2020/03/10 14:54:26 by fkante           ###   ########.fr       */
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
			sm->state = E_ERROR;
	}
	return (size);
}

uint8_t			ant(t_st_machine *sm, t_vector *line)
{
	uint8_t			ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else
	{
		sm->state = E_ROOM;
		sm->lemin->nb_ants = get_nb_of_ants(sm, line);
		add_line_to_output(sm, line, ANT);
	}
	return (ret);
}
