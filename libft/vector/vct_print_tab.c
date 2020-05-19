/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_print_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:27:37 by fkante            #+#    #+#             */
/*   Updated: 2020/05/19 11:02:44 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include "ft_printf.h"

/*
**	Print the table of vectors with there respective index and a new line.
*/

void	vct_print_tab(t_vector **tab)
{
	size_t	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			ft_printf("vector[%i] = ", i);
			vct_print(tab[i]);
			ft_printf("\n");
			i++;
		}
	}
}
