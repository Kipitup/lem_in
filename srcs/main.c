/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:13:27 by amartino          #+#    #+#             */
/*   Updated: 2020/04/14 15:52:09 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin	*lemin;

	lemin = init();
	if (lemin != NULL)
	{
		print_hashmap(lemin->room);
		print_adj_list(lemin->link);
		vct_print(lemin->output);
		ft_printf("\n\nNB OF ANTS: %zu\n", lemin->nb_ants);
		if (lemin->link != NULL)
			init_sol(lemin);
		if (lemin->result != NULL && lemin->result->graph != NULL)
		{
			print_adj_list(lemin->result->graph);
			ft_printf("--------------------------------------\n");
			bfs_list(lemin->result);
			for (int i = 0; lemin->result->path->contents[i] != NULL; i++)
				print_path(lemin->result->path->contents[i]);
		}
	}
	clean_lemin(&lemin);
	return (SUCCESS);
}

// __attribute__((destructor))void	dest_end()
// {
// 	ft_printf("coucou\n");
// 	while(1);
// }

//the path need to be store from the smallest to highest
//need the lenght of each path
//need to dispatch correctly te last ants in regards of the paths' lenght
//need to clear the path of all ants (when all ants have been sent in the path)

//func(t_darray *path, t_vector *output, size_t ant_total)
//{
//	size_t		i;
//	size_t		ant;
//
//	ant = 1;
//	while (ant <= ant_total)
//	{
//		i = 0;
//		while (i <= path->end)
//		{
//			path->contentp[i]->ant = ant;
//			add_next_ant_move(path->content[i], output);
//			i++;
//			ant++;
//		}
//		vct_addchar(output, '\n');
//	}
//}
//
//uint8_t		add_next_ant_move(t_path *room, t_vector *output)
//{
//	uint8_t		ret;
//
//	ret = FALSE;
//	if (room->next != NULL)
//	{
//		room->next->ant = room->ant;
//		ret = add_next_ant_move(room->next, output);
//	}
//	if (room->ant > 0)
//	{
//		vct_addchar(output, 'L');
//		vct_addnb(output, room->ant);
//		vct_addchar(output, '-');
//		vct_addstr(output, room->name);
//		vct_addchar(output, ' ');
//		ret = TRUE;
//	}
//	return (ret);
//}
