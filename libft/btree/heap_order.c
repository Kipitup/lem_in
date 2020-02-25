/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 11:03:55 by amartino          #+#    #+#             */
/*   Updated: 2020/02/21 08:54:02 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	swap(t_heap *heap, size_t parent, size_t child)
{
	int32_t		tmp;

	tmp = heap->A[parent];
	heap->A[parent] = heap->A[child];
	heap->A[child] = tmp;
}

void 	is_parent_valid(t_heap *heap, size_t child)
{
	size_t		parent;

	parent = get_heap_parent(child);
	if ((heap->type == MIN_HEAP && heap->A[parent] > heap->A[child]) == TRUE
	 || (heap->type == MAX_HEAP && heap->A[parent] < heap->A[child]) == TRUE)
	{
		swap(heap, parent, child);
		is_parent_valid(heap, parent);
	}
}

void	heapify(t_heap *heap, size_t parent)
{
	size_t		l;
	size_t		r;
	size_t		extremum;

	l = get_left_child(parent);
	l = (int32_t)l > heap->A[HEAP_SIZE] ? parent : l;
	r = get_right_child(parent);
	r = (int32_t)r > heap->A[HEAP_SIZE] ? parent : r;
	if (heap->type == MIN_HEAP)
	{
		extremum = heap->A[parent] > heap->A[l] ? l : parent;
		extremum = heap->A[extremum] > heap->A[r] ? r : extremum;
	}
	else
	{
		extremum = heap->A[parent] < heap->A[l] ? l : parent;
		extremum = heap->A[extremum] < heap->A[r] ? r : extremum;
	}
	if (extremum != parent)
	{
		swap(heap, parent, extremum);
		heapify(heap, extremum);
	}
}
