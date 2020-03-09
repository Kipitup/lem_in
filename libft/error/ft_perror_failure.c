/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_failure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:35:04 by amartino          #+#    #+#             */
/*   Updated: 2020/03/09 16:07:35 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int8_t		ft_perror_failure(char *str, const char *file, int line)
{
	if (str != NULL && file != NULL)
		ft_dprintf(STD_ERR, "{c_magenta}[{c_end}%s : %d{c_magenta}]{c_end}\
 {c_red}Error: %s{c_end}\n", file, line, str);
	return (FAILURE);
}
