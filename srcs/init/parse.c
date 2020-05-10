/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/05/10 18:22:10 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		parse(t_st_machine *sm)
{
	t_vector				*line;
	static t_state_func		parser[4] = {ant, room, room_link, command};
	int8_t					ret;
	uint8_t					shoud_read_nl;
	
	line = NULL;
	shoud_read_nl = TRUE;
	while (sm->state != E_END && sm->state > E_ERROR)
	{
		if (shoud_read_nl == TRUE)
		{
			vct_del(&line);
			ret = vct_read_line(STD_IN, &line);
		}
		if (ret == SUCCESS)
			sm->state = E_END;
		else if (ret == FAILURE)
			sm->state = READ_LINE_ERR;
		else
			shoud_read_nl = parser[sm->state](sm, line);
	}
	vct_del(&line);
	vct_read_line(CLEANUP, &line);
}
