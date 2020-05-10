/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 20:16:35 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/10 19:44:46 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static ssize_t	print_and_reset(char *buffer, size_t *buffer_index, char *line,
		size_t len)
{
	ssize_t			ret;

	ret = write(1, buffer, *buffer_index);
	ft_strclr(buffer);
	if (len < LEMIN_BUFF_SIZE - 1)
	{
		*buffer_index = len;
		ft_memcpy(buffer, (void*)line, len);
	}
	else
	{
		ret = write(1, line, len);
		*buffer_index = 0;
	}
	return (ret);
}

/*
**	The check (LEMIN_BUFF_SIZE - 2) make sure we have the space for the line +
**	a new line.
*/
size_t		add_to_buffer(char *line, size_t len, uint8_t state)
{
	static char 	buffer[LEMIN_BUFF_SIZE];
	static size_t	buffer_index = 0;
	ssize_t			ret;

	ret = SUCCESS;
	if (buffer_index + len > LEMIN_BUFF_SIZE - 2)
		ret = print_and_reset(buffer, &buffer_index, line, len);
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
	else if (state == PRINT)
		ret = write(1, buffer, buffer_index);
	if (ret <= FAILURE)
		error_management(STD_OUT_CLOSE);
	return (buffer_index);
}
