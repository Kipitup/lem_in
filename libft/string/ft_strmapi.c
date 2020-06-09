/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:29:42 by fkante            #+#    #+#             */
/*   Updated: 2020/06/09 11:08:16 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(size_t, char))
{
	size_t		i;
	size_t		len;
	char		*tmp;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	if (!(tmp = (char *)malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		tmp[i] = f(i, s[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
