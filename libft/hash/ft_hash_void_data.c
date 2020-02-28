/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:25:03 by fkante            #+#    #+#             */
/*   Updated: 2020/02/28 11:49:05 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** input:
**	data	- data to hash
**	hval	- previous hash value or 0 if first call
** reasoning behind the 5381 DJB magic constant:
** stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function
*/

uint32_t	ft_hash_void_data(void *data, uint32_t *previous_hash)
{
	t_vector	*vct_data;
	uint32_t	hash_val;
	size_t		i;

	(void)previous_hash;
	vct_data = vct_newstr((char*)data);
	hash_val = DJB_HASH_CONSTANT;
	i = 0;
	while (i < vct_data->len)
	{
		hash_val = ((hash_val << 5) + hash_val) + vct_getchar_at(vct_data, i);
		i++;
	}
	return (hash_val);
}
