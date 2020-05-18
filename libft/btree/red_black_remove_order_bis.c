/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_remove_order_bis.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:57:36 by francis           #+#    #+#             */
/*   Updated: 2020/05/18 22:58:26 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void			delete_case_6(t_rb_tree *node)
{
	t_rb_tree	*sibling;

	ft_printf("delete case 6\n");
	sibling = get_sibling(node);
	sibling->color = node->parent->color;
	node->parent->color = BLACK;
	if (node == node->parent->left)
	{
		sibling->right->color = BLACK;
		left_rotate(node->parent);
	}
	else
	{
		sibling->left->color = BLACK;
		right_rotate(node->parent);
	}
}
