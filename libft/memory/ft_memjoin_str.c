/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:00:55 by fkante            #+#    #+#             */
/*   Updated: 2019/05/09 12:28:46 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoin_str(char const *str_first, char const *str_last)
{
	int		i;
	int		len_first;
	int		len_last;
	char	*str_new;

	if (str_first == NULL || str_last == NULL)
		return (NULL);
	i = 0;
	len_first = ft_strlen(str_first);
	len_last = ft_strlen(str_last);
	if (!(str_new = (char *)malloc(len_first + len_last + 1)))
		return (NULL);
	while (i < len_first)
	{
		str_new[i] = str_first[i];
		i++;
	}
	while (i < len_first + len_last)
	{
		str_new[i] = str_last[i - len_first];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
