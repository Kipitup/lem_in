/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 13:28:27 by amartino          #+#    #+#             */
/*   Updated: 2020/02/26 21:46:45 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint8_t	is_it_all_digit(t_vector *line)
{
	size_t		i;
	size_t		len;
	int8_t		ret;

	i = (vct_getchar_at(line, 0) == '-') ? 1 : 0;
	len = vct_len(line);
	while (i < len)
	{
		ret = ft_isdigit(vct_getchar_at(line, i));
		if (ret == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	add_line_to_output(t_st_machine *sm, t_vector *line, uint8_t type)
{
	if (type == COMMENT)
		vct_pushstr(line, "\033[0m");
	else if (type == COMMAND)
		vct_pushstr(line, "\033[4m");
	else if (type == SPECIAL_ROOM)
		vct_pushstr(line, "\033[0;32m");
	else
		vct_pushstr(line, "\033[0;37m");
	vct_addstr(line, "\033[0m\n");
	vct_cat(sm->lemin->output, line);
	if (sm->lemin->output == NULL)
		sm->state = E_ERROR;
}

uint8_t		check_for_comment_or_command(t_st_machine *sm, t_vector *line)
{
	uint8_t	ret;

	ret = TRUE;
	if (vct_chr_str(line, "##") == START)
	{
		sm->state = E_COMMAND;
		ret = FALSE;
	}
	else
		add_line_to_output(sm, line, COMMENT);
	return (ret);
}
