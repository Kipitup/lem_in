/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/04/05 20:56:54 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
    t_lemin	*lemin;

    lemin = init();
    if (lemin != NULL)
    {
        //print_hashmap(lemin->room);
        //print_adj_list(lemin->link);
        //vct_print(lemin->output);
        if (lemin->link != NULL)
           init_sol(lemin);
        if (lemin->result->graph != NULL)
            print_adj_list(lemin->result->graph);
        ft_printf("--------------------------------------\n");
        bfs_list(lemin->result);
        //ft_printf("\n\nNB OF ANTS: %zu\n", lemin->nb_ants);
    }
    else
        ft_dprintf(STD_ERR, "error\n");
    clean_lemin(&lemin);
    // need to free sol when its over
    return (SUCCESS);
}

// __attribute__((destructor))void	dest_end()
// {
// 	ft_printf("coucou\n");
// 	while(1);
// }
