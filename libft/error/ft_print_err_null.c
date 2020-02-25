/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err_null.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:34:27 by amartino          #+#    #+#             */
/*   Updated: 2020/02/04 18:24:27 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		*ft_print_err_null(char *str, int8_t fd)
{
	if (str && *str != '\0')
		ft_dprintf(fd, "Error: %s\n", str);
	return (NULL);
}
