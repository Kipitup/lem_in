/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tool_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 22:59:04 by francis           #+#    #+#             */
/*   Updated: 2020/05/18 22:59:41 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void		clean_rb_tree(t_rb_tree **root)
{
	if (*root == NULL)
		return ;
	clean_rb_tree(&((*root)->right));
	clean_rb_tree(&((*root)->left));
	ft_memdel((void**)root);
}
