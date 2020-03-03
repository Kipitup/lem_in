/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:38:56 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 13:26:00 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	char	test[] = "salut ca va ?";
	void	*content;
	char	*new_content;

	content = ft_memalloc(ft_strlen(test) + 1);
	ft_strcpy((char *)content, test);
	new_content = (char*)ft_realloc(content, 5);
	for (int i = 0; i < 4; i++)
		ft_printf("new_content = %c\n", new_content[i]++);
	return (0);
}
