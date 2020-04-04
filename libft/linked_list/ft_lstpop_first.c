/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 15:46:39 by francis           #+#    #+#             */
/*   Updated: 2020/04/04 15:48:49 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_first(t_list **alst)
{
	t_list	*new_first;

	if (alst != NULL && *alst != NULL)
        {
        	new_first = (*alst)->next;
	        free(*alst);
        	*alst = new_first;
        }
}
