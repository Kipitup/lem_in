/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_low.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:01:11 by amartino          #+#    #+#             */
/*   Updated: 2020/01/17 15:33:32 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_get_low(int32_t *tab, size_t size)
{
	int32_t		low;
	size_t		i;

	i = 0;
	low = 0;
	while (i < size)
	{
		if (tab[low] > tab[i])
			low = i;
		i++;
	}
	return (low);
}
