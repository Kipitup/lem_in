/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_special_case.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:54:42 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/18 23:46:16 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int8_t	start_is_connected_to_end(t_network *net, size_t nb_ants)
{
	char		*nb_str;
	t_path		*end;
	size_t		curr_ant;
	int8_t		ret;

	ret = SUCCESS;
	curr_ant = 0;
	end = ((t_path*)net->all_path->contents[0])->next;
	while (curr_ant < nb_ants)
	{
		add_to_buffer("L", 1, ADD_NO_NEW_LINE);
		nb_str = ft_itoa(curr_ant);
		if (nb_str == NULL)
			return (error_management(MALLOC_ERR));
		add_to_buffer(nb_str, ft_strlen(nb_str), ADD_NO_NEW_LINE);
		ft_strdel(&nb_str);
		add_to_buffer("-", 1, ADD_NO_NEW_LINE);
		add_to_buffer(end->name, ft_strlen(end->name), ADD_NO_NEW_LINE);
		add_to_buffer(" ", 1, ADD_NO_NEW_LINE);
		curr_ant++;
	}
	add_to_buffer("\n", 1, ADD_NO_NEW_LINE);
	return (ret);
}
