/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 15:40:53 by amartino          #+#    #+#             */
/*   Updated: 2020/02/23 18:53:20 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		replace_node(t_rb_tree *node, t_rb_tree *child)
{
	child->parent = node->parent;
	if (node == node->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;
}

void		delete_child(t_rb_tree *node)
{
	t_rb_tree	*child;

	child = (node->right == NULL) ? node->left : node->right;
	if (child != NULL)
		replace_node(node, child);
	else
		child = node;
	if (node->color == BLACK)
	{
		if (child->color == RED)
			child->color = BLACK;
		else
			delete_case_1(child);
	}
	ft_memdel((void**)&node);
}

t_rb_tree	*swap_key_with_successor(t_rb_tree *node, int32_t key)
{
	t_rb_tree	*to_delete;
	t_rb_tree	*successor;

	while (key != node->key)
	{
		node = (key > node->key) ? node->right : node->left;
	}
	to_delete = node;
	successor = (node->right != NULL) ? node->right : node;
	while (successor->left != NULL)
	{
		successor = successor->left;
	}
	to_delete->key = successor->key;
	to_delete = successor;
	return (to_delete);
}

t_rb_tree	*delete(t_rb_tree *node, int32_t key)
{
	t_rb_tree	*to_delete;

	if (node != NULL)
	{
		to_delete = swap_key_with_successor(node, key);
		delete_child(to_delete);
		node = get_root(node);
	}
	return (node);
}
