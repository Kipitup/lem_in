/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_rear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/04 15:39:08 by francis           #+#    #+#             */
/*   Updated: 2020/04/04 15:43:53 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_rear(t_list **alst, t_list *new)
{
    t_list	*tmp;

    tmp = NULL;
    if (new != NULL)
    {
        if (*alst != NULL)
            tmp = *alst;
        else
            *alst = new;
        if (tmp != NULL)
        {
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = new;
        }
    }
}
