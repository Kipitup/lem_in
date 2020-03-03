/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:22:18 by fkante            #+#    #+#             */
/*   Updated: 2020/03/02 10:31:36 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashmap.h"

int		main(int ac, char **av)
{
	uint32_t	hval;

	(void)ac;
	hval = ft_hash_void_data(av[1]);
	ft_printf("input = %s\thval = %u\n", av[1], hval);
	return (0);
}
