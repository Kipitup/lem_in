/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:26:09 by fkante            #+#    #+#             */
/*   Updated: 2020/03/11 21:02:59 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static size_t	word_count(t_vector *vct_input, char c)
{
	char	*str;
	size_t	index;
	size_t	count;
	size_t	len;

	str = vct_getstr(vct_input);
	len = vct_len(vct_input);
	index = 0;
	count = 0;
	if (str != NULL)
	{
		while (index < len)
		{
			if (str[index] != c)
				count++;
			while (str[index] != c && index < len)
				index++;
			while (str[index] == c && index < len)
				index++;
		}
	}
	return (count);
}

static t_vector **vct_fill(t_vector *vct_input, char c, t_vector **vct_tab,
		size_t count)
{
	t_vector	*dup;
	char		*str;
	size_t		len;
	size_t		i;

	len = vct_len(vct_input);
	str = vct_getstr(vct_input);
	i = 0;
	dup = NULL;
	while (i < count)
	{
		while (str[0] == c)
			vct_pop_from(vct_input, 1, 0);
		vct_del(&dup);
		dup = vct_ndup(vct_input, vct_chr(vct_input, c));
		vct_tab[i] = vct_newstr(vct_getstr(dup));
		vct_pop_from(vct_input, vct_chr(vct_input, c), 0);
		if (vct_tab[i] == NULL)
		{
			vct_del_tab_content(vct_tab);
			break ;
		}
		i++;
	}
	vct_del(&dup);
	if (i == count)
		vct_tab[i] = NULL;
	return (vct_tab);
}

t_vector	**vct_split(t_vector *vct_input, char c)
{
	t_vector	**vct_tab;
	size_t		count_word;

	vct_tab = NULL;
	if (vct_input != NULL)
	{
		count_word = word_count(vct_input, c);
		vct_tab = ft_memalloc((count_word + 1) * sizeof(t_vector*));
		if (vct_tab != NULL)
			vct_tab = vct_fill(vct_input, c, vct_tab, count_word);
	}
	return (vct_tab);
}
