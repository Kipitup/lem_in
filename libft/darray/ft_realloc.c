/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <fkante@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:25:17 by fkante            #+#    #+#             */
/*   Updated: 2020/03/04 19:15:41 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "darray.h"


/*
** Bon en écrivant je me suis rendu compte de quelque problèmes, je te laisse les
** les traces pour que tu puisses comprendre mon raisonnement.
**
** a mon avis le fait que tmp soit en void ** fait que tu pourras jamais faire
** memcpy de tout ton array d'un coup. Si on regarde, le principe de la heap c'est
** que ca malloc a des endroits un peu random donc chaque tmp[i] est dans un endroit
** qui a probablement rien a voir avec l'adressede tmp.
** Donc je pense qu'il va falloir que tu boucle de
** for (int i = 0; i < array->end; i++)
** {
** 	ft_memcpy(tmp[i], array->contents[i], array->element_size)
** }
**
** bon et enfaisant ça je me suis rendu compte que c'était sans fin.. parce que si
** je veux faire un tableau de vector. on va devoir memcpy ce qu'il ya dans vector->str
** or vue que c'est sur la heap, ca sera n'importe ou...
**
** finalement la solution c'est juste de realloc un nouveau void **tmp
** avec pour taille : ((array->max + array->expand_rate) * array->element_size)
** et ensuite :
** for (int i = 0; i < array->end; i++)
** {
** 		tmp[i] = array->contents[i];
** }
** puis darray_destroy(&array).
** j'insiste sur le destroy only et pas le clear and destroy. on veut juste free
** l'ancien conteneur pas ce qu'il y a à l'intérieur.
**
** en plus c'est beaucoup plus rapide. on se fait pas chier a tout ré-allouer.
** a mon avis c'est comme ca que realloc fait, parce que lui aussi va pas s'amuser
** a tout free et tout réallouer. il va juste relinker les adresses correctement quoi
**
** comme ça on agis vraiment comme une liste chainé, on touche pas a la structure,
** seulement à la chaine.
*/

void	**ft_realloc(t_darray *array, size_t new_size, size_t old_size)
{
	void	**tmp;

	tmp = NULL;
	if (array != NULL)
	{
		if (new_size > 0)
		{
			tmp = ft_memalloc(new_size);
			if (tmp != NULL)
			{
				(new_size > old_size) ? ft_memcpy(tmp, array->contents, old_size)
					: ft_memcpy(tmp, array->contents, new_size);
				if (tmp == NULL)
					ft_print_err_failure("tmp is NULL after cpy", STD_ERR);
				darray_clear(&array);
			}
		}
	}
	else
		ft_print_err_failure("realloc failed / array is NULL", STD_ERR);
	return (tmp);
}
