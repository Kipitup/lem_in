/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:35:22 by fkante            #+#    #+#             */
/*   Updated: 2020/02/26 19:40:19 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word_count(char const *s, char c)
{
	size_t		count;

	count = 0;
	while (*s)
	{
		if (*s != c)
			count++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static void		ft_clean(char **tab, int i)
{
	while (--i >= 0)
		ft_strdel(&tab[i]);
	free(tab);
	tab = NULL;
}

static char		**ft_fill(char const *s, char c, char **tab, int count)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < count)
	{
		j = 0;
		k = 0;
		while (*s == c && *s)
			s++;
		while ((s[j] != c) && s[j])
			j++;
		if (!(tab[i] = (char*)ft_memalloc(sizeof(char) * (j + 1))))
		{
			ft_clean(tab, i);
			return (NULL);
		}
		while (--j >= 0)
			tab[i][k++] = (char)*s++;
		tab[i][k] = '\0';
	}
	tab[i] = 0;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	if (!(tab = (char**)ft_memalloc(sizeof(char *) * (count + 1))))
		return (NULL);
	return (ft_fill(s, c, tab, count) ? tab : NULL);
}
