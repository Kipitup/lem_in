/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 11:05:11 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/10 21:43:05 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Here net->path is not freed because it was not allocated in network but from
**	another structure. The free will be done there.
*/

static int8_t		push_next_ant_and_move_other(t_path *room, size_t ant)
{
	char		*nb_str;
	int8_t		ret;

	ret = SUCCESS;
	if (room->next != NULL)
		ret = push_next_ant_and_move_other(room->next, room->ant_nb);
	room->ant_nb = ant;
	if (ant > 0 && ret == SUCCESS)
	{
		add_to_buffer("L", 1, ADD_NO_NEW_LINE);
		nb_str = ft_itoa(room->ant_nb);
		if (nb_str == NULL)
			return (error_management(MALLOC_ERR));
		add_to_buffer(nb_str, ft_strlen(nb_str), ADD_NO_NEW_LINE);
		ft_strdel(&nb_str);
		add_to_buffer("-", 1, ADD_NO_NEW_LINE);
		add_to_buffer(room->name, ft_strlen(room->name), ADD_NO_NEW_LINE);
		add_to_buffer(" ", 1, ADD_NO_NEW_LINE);
	}
	return (ret);
}

static size_t		compute_next_line(t_network *net, size_t nb_ants,
		size_t curr_ant, int8_t *ret)
{
	t_path		*room_after_start;
	size_t		i;

	i = 0;
	while (i < net->nb_of_usable_flow)
	{
		room_after_start = ((t_path*)net->all_path->contents[i])->next;
		if (curr_ant <= nb_ants && net->flow[i].capacity > 0)
		{
			*ret	= push_next_ant_and_move_other(room_after_start, curr_ant);
			net->flow[i].capacity--;
			curr_ant++;
		}
		else
			*ret = push_next_ant_and_move_other(room_after_start, 0);
		i++;
	}
	return (curr_ant);
}

static int8_t		apply_solution(t_network *net, size_t nb_ants)
{
	size_t		curr_ant;
	size_t		line_total;
	int8_t		ret;

	ret = SUCCESS;
	curr_ant = 1;
	line_total = net->flow[0].len + net->flow[0].capacity;
	while (line_total > 0 && ret == SUCCESS)
	{
		curr_ant = compute_next_line(net, nb_ants, curr_ant, &ret);
		add_to_buffer("\n", 1, ADD_NO_NEW_LINE);
		line_total--;
	}
	return (ret);
}

/*
**	The number of line of the output will be: flow[0].len + flow[0].capacity.
*/
static t_network	*choose_best_solution(t_solution *result)
{
	t_network	*best;
	t_network	*tmp;
	uint32_t	nb_line_best;
	uint32_t	nb_line_tmp;

	best = result->net;
	while (result->next != NULL)
	{
		result = result->next;
		tmp = result->net;
		if (best != NULL && tmp != NULL)
		{
			nb_line_best = best->flow[0].len + best->flow[0].capacity;
			nb_line_tmp = tmp->flow[0].len + tmp->flow[0].capacity;
			if (nb_line_best > nb_line_tmp)
				best = tmp;
		}
	}
	return (best);
}

void				print_final_output(t_lemin *lemin)
{
	t_network	*net;
	int8_t		ret;

	if (lemin != NULL && lemin->result != NULL)
	{
		net = choose_best_solution(lemin->result);
		if (net != NULL)
		{
			if (VISU == TRUE)
				init_file_for_visu(lemin->link, net);
			ret = apply_solution(net, lemin->nb_ants);
			if (ret == SUCCESS)
				add_to_buffer(NULL, 0, PRINT);
		}
		else
			ft_perror("No path between start and end", __FILE__, __LINE__);
	}
}
