/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:15:55 by amartino          #+#    #+#             */
/*   Updated: 2020/02/21 09:06:29 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	insert_node(t_heap *heap, int32_t nb, size_t index)
{
	heap->A[index] = nb;
	heap->A[HEAP_SIZE]++;
	is_parent_valid(heap, index);
}

void	delete_root(t_heap *heap)
{
	size_t	size;

	size = heap->A[HEAP_SIZE];
	heap->A[ROOT] = heap->A[size];
	heap->A[size] = 0;
	heap->A[HEAP_SIZE]--;
	heapify(heap, ROOT);
}

void	fill_tree(t_heap *heap, int32_t *tab, size_t size)
{
	size_t		i;
	size_t		parent_index;

	i = 1;
	parent_index = 1;
	heap->A[1] = tab[0];
	heap->A[HEAP_SIZE]++;;
	while (i < size)
	{
		insert_node(heap, tab[i], get_left_child(parent_index));
		i++;
		if (i < size)
			insert_node(heap, tab[i], get_right_child(parent_index));
		i++;
		parent_index++;
	}
}

t_heap	*heap_tree(int32_t *tab, size_t size, uint8_t type)
{
	t_heap		*heap;

	heap = ft_memalloc(sizeof(t_heap));
	if (heap != NULL)
		heap->A = ft_memalloc(sizeof(int32_t) * (size + 1));
	if (heap == NULL || heap->A == NULL)
		ft_memdel((void**)&heap);
	else
	{
		heap->type = type;
		heap->A[HEAP_SIZE] = 0;
		fill_tree(heap, tab, size);
	}
	return (heap);
}
