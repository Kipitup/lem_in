/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:26:09 by fkante            #+#    #+#             */
/*   Updated: 2020/04/09 10:31:53 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
** 	Splits the input vector into multiple vectors separated by one or more
**	of the characters.
**	Pointers to the vectors are stored in successive elements in the array
**	pointed to by vct_tab.
**
**	One would of course keep track of the table created. The content and 
**	the table should be deleted, when its use is done.
*/

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

static void		fill(t_vector *vct_input, t_vector **vct_tab, char c,
						size_t tab_index)
{
	t_vector	*dup;
	char		*str;
	size_t		len;
	size_t		index;

	dup = NULL;
	len = vct_len(vct_input);
	str = vct_getstr(vct_input);
	while (str[0] == c)
		vct_pop_from(vct_input, 1, 0);
	index = vct_chr(vct_input, c);
	dup = vct_ndup(vct_input, index);
	vct_tab[tab_index] = vct_newstr(vct_getstr(dup));
	vct_pop_from(vct_input, index, 0);
	vct_del(&dup);
}

static t_vector	**vct_fill(t_vector *vct_input, t_vector **vct_tab, char c,
							size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		fill(vct_input, vct_tab, c, i);
		if (vct_tab[i] == NULL)
		{
			vct_del_tab_content(vct_tab);
			break ;
		}
		i++;
	}
	if (i == count)
		vct_tab[i] = NULL;
	return (vct_tab);
}

t_vector		**vct_split(t_vector *vct_input, char c)
{
	t_vector	**vct_tab;
	t_vector	*dup_input;
	size_t		count_word;

	vct_tab = NULL;
	dup_input = vct_dup(vct_input);
	if (dup_input != NULL)
	{
		count_word = word_count(dup_input, c);
		vct_tab = ft_memalloc((count_word + 1) * sizeof(t_vector*));
		if (vct_tab != NULL)
			vct_tab = vct_fill(dup_input, vct_tab, c, count_word);
	}
	vct_del(&dup_input);
	return (vct_tab);
}
