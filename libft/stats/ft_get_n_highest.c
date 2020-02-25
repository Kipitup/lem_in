/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_n_highest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:49:09 by amartino          #+#    #+#             */
/*   Updated: 2020/01/23 21:16:31 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

ssize_t		ft_get_n_highest(int32_t *tab, size_t nth, size_t start,
								size_t limit)
{
	t_heap	*heap;
	size_t	i;

	i = start;
	heap = heap_tree((tab + start), limit, MAX_HEAP);
	if (heap == NULL || nth == 0)
		return (FAILURE);
	while (nth > 1)
	{
		delete_root(heap);
		nth--;
	}
	while (i < (limit + start))
	{
		if (tab[i] == heap->A[ROOT])
			break ;
		i++;
	}
	clean_heap_tree(&heap);
	return (i);
}
