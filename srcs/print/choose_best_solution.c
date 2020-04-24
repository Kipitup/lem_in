/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_best_solution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <a.martino@sutdent.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:54:12 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/24 10:27:03 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_debug_network(t_network *net)
{
	size_t	i;

	i = 0;
	while (net != NULL && i < net->nb_of_flow)
	{
		ft_dprintf(STD_ERR, "flow[%zu]:\n\t- len is    %zu\n\tcapacity is %zu\n",
				i, net->flow[i].len, net->flow[i].capacity);
		i++;
	}
}

/*
**	We substract the diff from the nb_ants ant dispatch it equally among each
**	flow. Then add the diff between flow[last].len - flow[i].len w/ 0 < i < last
*/
static void			set_capacity(t_network *net, size_t nb_ants, int64_t diff)
{
	size_t		i;
	size_t		last;
	uint32_t	rest;

	i = 0;
	rest = (nb_ants - diff) % net->nb_of_flow;
	while (i < net->nb_of_flow)
	{
		net->flow[i].capacity = (nb_ants - diff) / net->nb_of_flow;
		if (rest > 0)
		{
			net->flow[i].capacity++;
			rest--;
		}
		i++;
	}
	i = 0;
	last = net->nb_of_flow - 1;
	while (i < last)
	{
		net->flow[i].capacity += net->flow[last].len - net->flow[i].len;
		i++;
	}
}

/*
**	The len of each flow is define by then len of the path - 1;	
**
**	Diff is the sum of the difference between the biggest flow's and each other
**	flow's len.
**	diff = flow[last].len - flow[0].len + ... + flow[last].len - flow[i].len;
**	with 0 < i < last
**	Since the paths are stored in the ascending order, last.len > i.len.
*/
static void			set_network(t_network *net, size_t nb_ants)
{
	size_t		i;
	size_t		last;
	int64_t		len_diff;

	i = 0;
	len_diff = 0;
	while (i < net->nb_of_flow)
	{
		net->flow[i].len = ((t_path*)net->all_path->contents[i])->len - 1;
		i++;
	}
	i = 0;
	last = net->nb_of_flow - 1;
	while (i < last)
	{
		len_diff += net->flow[last].len - net->flow[i].len;
		i++;
	}
	set_capacity(net, nb_ants, len_diff);
}

static t_network	*init_and_set_network(t_darray *all_path, size_t nb_ants)
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

/*
**	The number of line of the output will be: flow[0].len + flow[0].capacity.
*/
t_network			*choose_best_solution(t_solution *result, size_t nb_ants)
{
	t_network	*best;
	t_network	*tmp;
	uint32_t	nb_line_best;
	uint32_t	nb_line_tmp;

	best = init_and_set_network(result->path, nb_ants);
	if (best == NULL)
		return (ft_perror_null(MALLOC_ERR, __FILE__, __LINE__));
	while (result->next != NULL)
	{
		result = result->next;
		tmp = init_and_set_network(result->path, nb_ants);
		if (tmp == NULL)
		{
			clean_network(&best);
			return (ft_perror_null(MALLOC_ERR, __FILE__, __LINE__));
		}
		nb_line_best = best->flow[0].len + best->flow[0].capacity;
		nb_line_tmp = tmp->flow[0].len + tmp->flow[0].capacity;
		nb_line_best > nb_line_tmp ? clean_network(&best) : clean_network(&tmp);
		if (nb_line_best > nb_line_tmp)
			best = tmp;
	}
	print_debug_network(best);
	return (best);
}
