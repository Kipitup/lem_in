/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <a.martino@sutdent.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:50:14 by amartino          #+#    #+#             */
/*   Updated: 2020/05/08 18:11:49 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		ft_perror(char *str, const char *file, int line)
{
	if (str != NULL)
	{
		if (DEBUG == ON && file != NULL)
		{
			ft_dprintf(STD_ERR, "{c_magenta}[{c_end}%s : %d{c_magenta}]{c_end}\
					{c_red}Error: %s{c_end}\n", file, line, str);
		}
		else
		{
			ft_dprintf(STD_ERR, "{c_red}Error: %s{c_end}\n", str);
		}
	}
}
