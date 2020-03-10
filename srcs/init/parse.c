/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/03/10 12:09:15 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		parse(t_st_machine *sm)
{
	t_vector				*line;
	static t_state_func		parser[4] = {ant, room, room_link, command};
	int8_t					ret;
	uint8_t					read_next_line;

	line = NULL;
	read_next_line = TRUE;
	while (sm->state != E_END && sm->state != E_ERROR)
	{
		if (read_next_line == TRUE)
		{
			vct_del(&line);
			ret = vct_read_line(STD_IN, &line);
		}
		if (ret == SUCCESS)
			sm->state = E_END;
		else if (ret == FAILURE)
			sm->state = E_ERROR;
		else
			read_next_line = parser[sm->state](sm, line);
	}
	vct_del(&line);
}
