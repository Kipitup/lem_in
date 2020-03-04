/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:38:56 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 15:20:41 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		main(void)
{
	char	test[] = "cafait8";
	void	*content_1;
	void	*content_2;
	char	*new_content;
	int		new_size = 10;
	int		old_size;

	content_1 = ft_memalloc(ft_strlen(test) + 1);
	ft_strcpy((char *)content, test);
	new_content = (char*)realloc(content_1, new_size);

	content_2 = ft_memalloc(ft_strlen(test) + 1);
	ft_strcpy((char *)content, test);
	old_size = ft_strlen(content);
	new_content = (char*)ft_realloc(content, new_size, old_size);
	
	return (0);
}
