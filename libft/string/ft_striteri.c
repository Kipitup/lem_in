/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:03:27 by fkante            #+#    #+#             */
/*   Updated: 2020/06/09 11:07:31 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(size_t, char *))
{
	size_t		i;
	size_t		len;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	len = (uint32_t)ft_strlen(s);
	while (i < len)
	{
		f(i, s + i);
		i++;
	}
}
