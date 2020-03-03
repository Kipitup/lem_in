/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room_link.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:41 by amartino          #+#    #+#             */
/*   Updated: 2020/03/03 16:02:07 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint8_t		room_link(t_st_machine *sm, t_vector *line)
{
	t_vector	*dup;
	size_t		index;
	uint8_t		ret;

	ret = TRUE;
	if (vct_getchar_at(line, START) == '#')
		ret = check_for_comment_or_command(sm, line);
	else if (vct_chr_count(line, '-') == 1)
	{
		index = vct_chr(line, '-');
		dup = vct_ndup(line, index);
		//check if the room existin hashmap else sm->state = E_ERROR;
		add_line_to_output(sm, line, ROOM_LINK);
		vct_del(&dup);
	}
	else
		sm->state = E_ERROR;
	return (ret);
}
