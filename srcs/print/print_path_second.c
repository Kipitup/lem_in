/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 12:08:06 by francis           #+#    #+#             */
/*   Updated: 2020/05/10 11:45:08 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path_and_vertices_used_more(t_path *path, t_graph *graph)
{
	t_path	*tmp;
	uint8_t	usable;

	if (path != NULL && graph != NULL)
	{
		print_path(path);
		tmp = path;
		ft_printf("{c_cyan}----------Vertex Used--------{c_end}\n");
		while (tmp != NULL)
		{
			if (graph->array[tmp->vertex].usable > 1 && tmp->vertex != 0)
			{
				usable = graph->array[tmp->vertex].usable;
				ft_printf("vertex[%d] used %d\n", tmp->vertex, usable);
			}
			tmp = tmp->next;
		}
		ft_printf("{c_cyan}-----------------------------{c_end}\n");
	}
}

void	print_all_links_to_vertex_used_more(t_graph *graph)
{
	size_t i;

	i = 1;
	while (i < graph->size)
	{
		if (graph->array[i].usable > 1)
		{
			ft_printf("---------------Node %d--------------\n", i);
			print_link_available(graph->array[i]);
		}
		i++;
	}
}

void	vertex_used_more(t_graph *graph)
{
	size_t i;

	i = 1;
	while (i < graph->size)
	{
		if (graph->array[i].usable > 1)
		{
			ft_printf("\n{c_cyan}Node used more{c_end}\n");
			break ;
		}
		i++;
	}
}

void	print_debug_network(t_network *net)
{
	size_t	i;

	i = 0;
	ft_dprintf(STD_ERR, "---------------------------------------------\n");
	while (net != NULL && i < net->nb_of_flow)
	{
		ft_dprintf(STD_ERR, "flow[%zu]:\n\t- len is  %zu\n\tcapacity is %zu\n",
				i, net->flow[i].len, net->flow[i].capacity);
		i++;
	}
	ft_dprintf(STD_ERR, "---------------------------------------------\n");
}

void	print_link_available(t_adj_list node)
{
	size_t		count;

	count = 0;
	while (node.head != NULL)
	{
		ft_printf("dest = %d\t", node.head->dest);
		ft_printf("available = %d\n", node.head->available);
		count++;
		node.head = node.head->next;
	}
	ft_printf("{c_yellow} %zu possible link{c_end}\n", count);
}
