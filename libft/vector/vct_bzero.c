/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_bzero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:05:32 by amartino          #+#    #+#             */
/*   Updated: 2020/05/19 10:58:48 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

/*
**	Fill the allocated bloc with '\0'
*/

void			vct_bzero(t_vector *vector)
{
	if (vector != NULL && vector->str != NULL)
	{
		ft_bzero(vector->str, vector->size);
		vector->len = 0;
	}
}
