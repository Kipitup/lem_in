/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:14:06 by fkante            #+#    #+#             */
/*   Updated: 2020/03/09 14:14:18 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				main(void)
{
	t_graph		*graph;
	size_t		size;
	int8_t		ret;

	size = 5;
	graph = NULL;
	graph = init_graph(size);
	if (graph != NULL)
	{
		ret = add_edge(graph, 0, 1);
		if (ret != FAILURE)
			ret = add_edge(graph, 0, 4);
		if (ret != FAILURE)
			ret = add_edge(graph, 1, 2);
		if (ret != FAILURE)
			ret = add_edge(graph, 2, 0);
		if (ret != FAILURE)
			ret = add_edge(graph, 3, 4);
		print_link(graph);
	}
	clean_graph(&graph);
	return (0);
}
