/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:27:45 by fkante            #+#    #+#             */
/*   Updated: 2020/03/02 14:13:50 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DARRAY_H
# define DARRAY_H

# include <stdlib.h>

# define DEFAULT_EXPAND_RATE	500

typedef struct	s_darray {
	int32_t	end;
	int32_t	max;
	size_t	element_size;
	size_t	expand_rate;
	void	**contents;
}				t_darray;

void		darray_set(t_darray *array, int32_t i, void *element);
void		*darray_get(t_darray *array, int32_t i);
void		*darray_remove(t_darray *array, int32_t i);
void		*darray_new(t_darray *array);
t_darray	*darray_create(size_t element_size, size_t initial_max);
int8_t		darray_expand(t_darray *array);
int8_t		darray_contract(t_darray *array);
int8_t		darray_push(t_darray *array, void *element);
void		*darray_pop(t_darray *array);
void		darray_destroy(t_darray *array);
void		darray_clear(t_darray *array);
void		darray_clear_destroy(t_darray *array);

/*
** ********************************  ERRORS ************************************
*/
# define SET_ABOVE_MAX			"darray attempt to set past max"
# define GET_ABOVE_MAX			"darray attempt to get past max"
# define ARRAY_SIZE_ZERO		"Can't use darray_new on 0 size darrays"
# define INITIAL_MAX_ZERO		"You must set an initial_max > 0"
# define NEWSIZE_ZERO			"To resize Darray, the newsize must be > 0"
# define FAILED_TO_EXPAND		"Failed to expand array to new size"
# define FAILED_TO_POP			"Attempt to pop from empty array"

#endif
