/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_for_visu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 11:57:52 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/24 09:44:41 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_link_to_file(t_graph *graph, int fd)
{
	size_t		i;
	t_adj_node	*node;

	i = 0;
	while (i < graph->size)
	{
		node = graph->array[i].head;
		while (node != NULL)
		{
			ft_dprintf(fd, "%zu-%zu\n", i, node->dest);
			node = node->next;
		}
		i++;
	}
}

static void		add_path_to_file(t_network *net, int fd)
{
	t_path		*tmp;
	size_t		i;

	i = 0;
	while (i <= net->all_path->end)
	{
		tmp = net->all_path->contents[i];
		while (tmp != NULL)
		{
			ft_dprintf(fd, "%zu ", tmp->vertex);
			tmp = tmp->next;
		}
		ft_dprintf(fd, "\n");
		i++;
	}
}

void			init_file_for_visu(t_graph *graph, t_network *net)
{
	int			fd;
	
	fd = open("/tmp/visu_lemin.txt", O_RDWR | O_CREAT | O_TRUNC , 0744);
	if (fd != FAILURE)
	{
		if (graph != NULL)
			add_link_to_file(graph, fd);
		if (net != NULL)
			add_path_to_file(net, fd);
	}
}
