/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/02/25 20:46:43 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ant(t_st_machine *sm, t_vector *line)
{
	(void)sm;
	(void)line;
	vct_addchar(line, '\n');
	vct_cat(sm->lemin->output_text, line);
}

void	room(t_st_machine *sm, t_vector *line)
{
	(void)sm;
	(void)line;
}

void	room_link(t_st_machine *sm, t_vector *line)
{
	(void)sm;
	(void)line;
}

void	command(t_st_machine *sm, t_vector *line)
{
	(void)sm;
	(void)line;
}

void	parse(t_st_machine *sm)
{
	t_vector			*line;
	static t_state_func	parser[4] = {ant, room, room_link, command};
	int8_t				ret;

	line = NULL;
	while (sm->state != E_END && sm->state != E_ERROR)
	{
		ret = vct_read_line(STD_IN, &line);
		if (ret == SUCCESS)
			sm->state = E_END;
		else if (ret == FAILURE)
			sm->state = E_ERROR;
		else
			parser[sm->state](sm, line);
		vct_del(&line);
	}
}
