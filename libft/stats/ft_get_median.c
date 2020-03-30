/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_median.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 15:49:05 by amartino          #+#    #+#             */
/*   Updated: 2020/03/29 16:29:14 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t		ft_get_median(int32_t *tab, size_t size)
{
	size_t		i;
	int32_t		median;
	int8_t		ret;

	i = 0;
	ret = ft_median(tab, size, &median);
	if (ret == FAILURE)
		return (FAILURE);
	while (i < size)
	{
		if (tab[i] == median)
			break ;
		i++;
	}
	return (i);
}
