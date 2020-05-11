/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:01:11 by amartino          #+#    #+#             */
/*   Updated: 2020/05/11 22:24:48 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t		ft_mean(int32_t *tab, size_t size)
{
	int32_t		total;
	int32_t		result;
	size_t		i;

	i = 0;
	result = 0;
	if (tab != NULL && size != 0)
	{
		total = tab[i];
		while (i < size)
		{
			total += tab[i];
			i++;
		}
		result = total / size;
	}
	if (tab == NULL)
		ft_perror("Input table is NULL", NULL, 0);
	else if (size == 0)
		ft_perror("Division by zero when looking for mean", NULL, 0);
	return (result);
}
