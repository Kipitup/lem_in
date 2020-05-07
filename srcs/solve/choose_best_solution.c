/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_best_solution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:54:12 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/07 16:14:08 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	We substract the diff from the nb_ants ant dispatch it equally among each
**	flow. Then add the diff between flow[last_index].len - flow[i].len
**	with 0 < i < last_index
*/
static void			set_capacity(t_network *net, size_t nb_ants, int64_t diff)
{
	size_t		i;
	uint32_t	rest;

	i = 0;
	rest = (nb_ants - diff) % (net->nb_of_usable_flow);
	while (i < net->nb_of_usable_flow)
	{
		net->flow[i].capacity = (nb_ants - diff) / (net->nb_of_usable_flow);
		if (rest > 0)
		{
			net->flow[i].capacity++;
			rest--;
		}
		i++;
	}
	i = 0;
	while (i < net->nb_of_usable_flow - 1)
	{
		net->flow[i].capacity += net->flow[net->nb_of_usable_flow - 1].len - net->flow[i].len;
		i++;
	}
}

/*
**	Diff is the sum of the difference between the biggest usable flow's and each
**	other flow's len. All the flow won't necessarily be usable. If the number of
**	ant is to small, only the fastest flow will be used.
**	diff = flow[last].len - flow[0].len + ... + flow[last].len - flow[i].len;
**	with 0 < i < last
**
**	Since the paths are stored in the ascending order, last.len > i.len.
*/
static size_t		calculate_diff(t_network *net, size_t nb_ants)
{
	size_t		i;
	size_t		last;
	size_t		len_diff;

	last = net->nb_of_flow - 1;
	while (last > 0)
	{
		i = 0;
		len_diff = 0;
		while (i < last)
		{
			len_diff += net->flow[last].len - net->flow[i].len;
			i++;
		}
		if (len_diff < nb_ants)
			break ;
		last--;
	}
	net->nb_of_usable_flow = last + 1;
	if (last == 0 && len_diff >= nb_ants)
		len_diff = 0;
	return (len_diff);
}

/*
**	The len of each flow is define by then len of the path - 1;
**
*/
static void			set_network(t_network *net, size_t nb_ants)
{
	size_t		i;
	size_t		len_diff;

	i = 0;
	while (i < net->nb_of_flow)
	{
		net->flow[i].len = ((t_path*)net->all_path->contents[i])->len - 1;
		i++;
	}
	len_diff = calculate_diff(net, nb_ants);
	set_capacity(net, nb_ants, len_diff);
}

t_network			*init_and_set_network(t_darray *all_path, size_t nb_ants)
{
	t_network	*net;

	net = NULL;
	if (all_path != NULL)
	{
		darray_remap_index(all_path);
		net = ft_memalloc(sizeof(t_network));
		if (net != NULL)
		{
			net->all_path = all_path;
			net->nb_of_flow = all_path->end + 1;
			net->flow = ft_memalloc(net->nb_of_flow * sizeof(t_flow));
			if (net->flow != NULL)
				set_network(net, nb_ants);
			else
				clean_network(&net);
		}
	}
	return (net);
}
