/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <a.martino@sutdent.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:06:02 by amartino          #+#    #+#             */
/*   Updated: 2020/04/05 16:45:44 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "ft_printf.h"

void	print_adj_list(t_graph *graph)
{
	t_adj_node	*node;
	size_t		i;

	i = 0;
	if (graph != NULL)
	{
		while (i < graph->size)
		{
			ft_printf("vertex %d\nhead", i);
			node = graph->array[i].head;
			while (node != NULL)
			{
				ft_printf(" -> %d", node->dest);
				node = node->next;
			}
			ft_printf("\n");
			i++;
		}
	}
}

void	print_adj_node(t_adj_list node)
{
	t_adj_node  *tmp;

	ft_printf("\n------------------------------------------------\\\n");
	tmp = node.head;
	ft_printf("Distance: %d\t\t\t\t\t|\n", node.distance);
	ft_printf("Usable: %d\t(0 for open / 1 for visited)\t|\n", node.usable);
	ft_printf("links");
	if (node.head == NULL)
		ft_printf("\t");
	while (node.head != NULL)
	{
		ft_printf(" -> %d", node.head->dest);
		node.head = node.head->next;
	}
	ft_printf("\t\t\t\t\t|");
	node.head = tmp;
	ft_printf("\n------------------------------------------------/\n");
}
