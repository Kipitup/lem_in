/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/03/12 14:17:35 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_solution      *init_sol(t_graph *graph)
{
    t_solution  *sol;

    sol = ft_memalloc(sizeof(t_solution));
    if (graph != NULL)
    {
        sol->path = darray_create(sizeof(t_graph*), DEFAULT_ARRAY_SIZE);
        sol->graph = ft_memalloc(sizeof(t_graph));
        if (sol->graph != NULL)
        {
            sol->graph->size = graph->size;
//            sol->graph->array = ft_dup_list(graph); function to be done;
        }
    }
    return (sol);
}
