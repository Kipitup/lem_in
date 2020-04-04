/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:46:24 by amartino          #+#    #+#             */
/*   Updated: 2020/04/04 14:23:38 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void  init_sol(t_lemin *lemin)
{
    lemin->result = ft_memalloc(sizeof(t_solution));
    if (lemin->result != NULL)
        lemin->result->graph = dup_adj_list(lemin->link);
}
