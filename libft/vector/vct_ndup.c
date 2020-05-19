/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vct_ndup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:56:01 by amartino          #+#    #+#             */
/*   Updated: 2020/05/19 11:05:50 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

/*
**	Return a duplicate portion (len) of the given vector.
*/

t_vector	*vct_ndup(t_vector *vector, size_t len)
{
	t_vector	*dup;

	dup = NULL;
	if (vector != NULL && vector->str != NULL)
	{
		if (len > vector->len)
			len = vector->len;
		dup = vct_new(len);
		if (dup != NULL)
		{
			if (vct_addnstr(dup, vector->str, len) == FAILURE)
				vct_del(&dup);
		}
	}
	return (dup);
}
