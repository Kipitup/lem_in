/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file_for_visu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 11:57:52 by amartinod         #+#    #+#             */
/*   Updated: 2020/04/22 14:38:22 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_file_for_visu(t_graph *graph)
{
	t_adj_node	*node;
	size_t		i;
	int			fd;
	
	i = 0;
	fd = open("/tmp/visu_lemin.txt", O_RDWR | O_CREAT | O_TRUNC , 0744);
	if (fd != FAILURE)
	{
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
}
