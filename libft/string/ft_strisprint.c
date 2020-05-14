/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:17:21 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/14 15:34:07 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisprint(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isprint((int)str[i]) == TRUE)
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}
