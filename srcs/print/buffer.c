/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:16:35 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/10 11:39:59 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_small_buff(char *buffer, char *line, size_t len)
{
	ft_strclr(buffer);
	ft_memcpy(buffer, (char*)line, (size_t)len);
}

/*
**	The check (LEMIN_BUFF_SIZE - 2) make sure we have the space for the line +
**	a new line.
*/

void		add_to_buffer(char *line, size_t len, uint8_t state)
{
	static char buffer[LEMIN_BUFF_SIZE];
	static int	buffer_index = 0;

	if (state == PRINT)
		write(1, buffer, buffer_index);
	else if (line != NULL)
	{
		if (buffer_index + len > LEMIN_BUFF_SIZE - 2)
		{
			write(1, buffer, buffer_index);
			buffer_index = len;
			ft_small_buff(buffer, line, len);
		}
		else
		{
			ft_memcpy(&buffer[buffer_index], line, len);
			buffer_index += len;
		}
		if (state == ADD_NEW_LINE)
		{
			buffer[buffer_index] = '\n';
			buffer_index++;
		}
	}
}
