/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 16:49:52 by francis           #+#    #+#             */
/*   Updated: 2020/04/08 17:34:12 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_solution *sol)
{
	t_darray	*array;
	t_path		*tmp;
	size_t		i;

	i = 0;
	if (sol != NULL && sol->path != NULL)
	{
		ft_printf("BFS paths found:\n");
		array = sol->path;
		i = 0;
		if (array != NULL)
		{
			tmp = darray_get(array, i);
			ft_printf("path[%d]: ", i++);
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
}
