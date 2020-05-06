/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 11:05:11 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/06 15:51:18 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_debug_network(t_network *net)
{
	size_t	i;

	i = 0;
	ft_dprintf(STD_ERR, "---------------------------------------------\n");
	while (net != NULL && i < net->nb_of_flow)
	{
		ft_dprintf(STD_ERR, "flow[%zu]:\n\t- len is    %zu\n\tcapacity is %zu\n",
				i, net->flow[i].len, net->flow[i].capacity);
		i++;
	}
	ft_dprintf(STD_ERR, "---------------------------------------------\n");
}

/*
**	Here net->path is not freed because it was not allocated in network but from
**	another structure. The free will be done there.
*/

static uint8_t	push_next_ant_and_move_other(t_path *room, t_vector *output,
		size_t ant)
{
	uint8_t		ret;

	ret = FALSE;
	if (room->next != NULL)
		ret = push_next_ant_and_move_other(room->next, output, room->ant_nb);
	room->ant_nb = ant;
	if (ant > 0)
	{
		write(1, "L", 1);
		ft_putnbr(room->ant_nb);
		write(1, "-", 1);
		ft_putstr(room->name);
		write(1, " ", 1);
		ret = TRUE;
	}
	return (ret);
}

static size_t	compute_next_line(t_network *net, t_vector *output,
		size_t nb_ants, size_t curr_ant)
{
	t_path		*room_after_start;
	size_t		i;

	i = 0;
	while (i < net->nb_of_usable_flow)
	{
		room_after_start = ((t_path*)net->all_path->contents[i])->next;
		if (curr_ant <= nb_ants && net->flow[i].capacity > 0)
		{
			push_next_ant_and_move_other(room_after_start, output, curr_ant);
			net->flow[i].capacity--;
			curr_ant++;
		}
		else
			push_next_ant_and_move_other(room_after_start, output, 0);
		i++;
	}
	return (curr_ant);
}

static void		apply_solution(t_network *net, t_vector *output, size_t nb_ants)
{
	size_t		curr_ant;
	size_t		line_total;

	curr_ant = 1;
	line_total = net->flow[0].len + net->flow[0].capacity;
	while (line_total > 0)
	{
		curr_ant = compute_next_line(net, output, nb_ants, curr_ant);
		write(1, "\n", 1);
		line_total--;
	}
}

void				print_final_output(t_lemin *lemin)
{
	t_network	*net;

	if (lemin != NULL)
	{
		net = choose_best_solution(lemin->result, lemin->nb_ants);
		//print_debug_network(net);
		vct_print(lemin->output);
		if (net != NULL)
		{
			if (VISU == TRUE)
				init_file_for_visu(lemin->link, net);
			apply_solution(net, lemin->output, lemin->nb_ants);
			clean_network(&net);
		}
	}
}
