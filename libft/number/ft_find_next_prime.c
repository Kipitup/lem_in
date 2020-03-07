/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <a.martino@sutdent.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:40:04 by amartino          #+#    #+#             */
/*   Updated: 2020/03/07 17:48:31 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t		ft_find_next_prime(uint32_t nb)
{
	uint32_t	prime;

	if (is_prime(nb) == TRUE)
		prime = nb;
	else
		ft_find_next_prime(nb + 1);
	return (prime);
}
