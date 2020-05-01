/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:49:52 by francis           #+#    #+#             */
/*   Updated: 2020/04/30 16:28:41 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_link_available(t_adj_list node)
{
	ft_printf("{c_yellow}------------ Link available ------------{c_end}\n");
	while (node.head != NULL)
	{
		ft_printf("dest = %d\t", node.head->dest);
		ft_printf("available = %d\n", node.head->available);
		node.head = node.head->next;
	}
}

void	print_all_links(t_graph *graph)
{
	size_t i;

	i = 0;
	while (i < graph->size)
	{
		ft_printf("---------------Node %d--------------\n", i);
		print_link_available(graph->array[i]);
		i++;
	}
}

void	print_path(t_path *path)
{
	t_path		*tmp;

	if (path != NULL)
	{
		ft_printf("BFS path found:\n");
		tmp = path;
		ft_printf("path: ");
		while (tmp != NULL)
		{
			if (tmp->vertex == 0)
				ft_printf("%d", tmp->vertex);
			else
				ft_printf(" -> %d", tmp->vertex);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}

void	print_all_path(t_darray *all_path)
{
	t_path	*path;
	size_t	i;

	i = 0;
	ft_printf("{c_green}------------ Path sequence ------------{c_end}\n");
	while (i <= all_path->end)
	{
		path = all_path->contents[i];
		if (path != NULL)
		{
	//		print_path(path);
			ft_printf("Path length = %d\n\n", path->len);
		}
		i++;
	}
}

void	print_all_solution(t_lemin *lemin)
{
	t_solution *begin;

	begin = lemin->result;
	while (lemin->result != NULL)
	{
		ft_printf("{c_blue}------------ Path sequence ------------{c_end}\n");
		print_all_path(lemin->result->path);
		lemin->result = lemin->result->next;
	}
	lemin->result = begin;
	rewind_solution(lemin);
}
