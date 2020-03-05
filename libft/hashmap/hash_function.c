/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:25:03 by fkante            #+#    #+#             */
/*   Updated: 2020/03/05 14:21:18 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "vector.h"

/*
** input:
**	data	- data to hash
**	hval	- previous hash value or 0 if first call
** reasoning behind the 5381 DJB magic constant:
** stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function
*/

uint32_t	ft_hash_void_data(void *data, size_t len)
{
	size_t		i;
	uint32_t	hash_val;

	i = 0;
	hash_val = DJB_HASH_CONSTANT;
	while (i < len)
	{
		hash_val = ((hash_val << 5) + hash_val) + ((unsigned char*)data)[i];
		i++;
	}
	return (hash_val);
}
