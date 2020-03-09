/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <a.martino@sutdent.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:50:14 by amartino          #+#    #+#             */
/*   Updated: 2020/03/09 16:06:06 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		ft_perror(char *str, const char *file, int line)
{
	if (str != NULL && file != NULL)
		ft_dprintf(STD_ERR, "{c_magenta}[{c_end}%s : %d{c_magenta}]{c_end}\
 {c_red}Error: %s{c_end}\n", file, line, str);
}
