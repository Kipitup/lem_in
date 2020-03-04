/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:38:56 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 09:49:47 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	char	test[] = "cafait8";
	void	*content;
	char	*new_content;
	int		size = 9;

	content = ft_memalloc(ft_strlen(test) + 1);
	ft_strcpy((char *)content, test);
	new_content = (char*)ft_realloc(content, size);
	for (int i = 0; i < size; i++)
		ft_printf("new_content = %c\n", new_content[i]++);
	return (0);
}
