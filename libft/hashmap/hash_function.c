/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:25:03 by fkante            #+#    #+#             */
/*   Updated: 2020/04/28 15:00:44 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include "libft.h"
#include "vector.h"

/*
** http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
*/
uint32_t		ft_fnv1a_hash(const void *data, size_t len)
{
	size_t					i;
	uint32_t				hash;
	static const uint32_t	fnv_prime = 16777619;
	static const uint32_t	offset_basis = 2166136261;

	i = 0;
	hash = offset_basis;
	while (i < len)
	{
		hash ^= ((char *)data)[i];
		hash *= fnv_prime;
		i++;
	}
	return (hash);
}

/*
** input:
**	data	- data to hash
**	hval	- previous hash value or 0 if first call
** reasoning behind the 5381 DJB magic constant:
** https://s.42l.fr/stackoverflow-magic-number-hash-function
*/

uint32_t		ft_hash_void_data(const void *data, size_t len)
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

uint32_t		ft_hash_str(const void *data, size_t len)
{
	size_t		i;
    uint32_t	hash;

	i = 0;
	hash = 0;
	while (i < len)
	{
        hash += ((char *)data)[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
		i++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (hash);
}
