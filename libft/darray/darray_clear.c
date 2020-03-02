
#include "darray.h"

void	darray_clear(t_array *array)
{
	size_t i;

	i = 0;
	if (array->element_size > 0) 
	{
		while (i < array->max)
		{
			if (array->contents[i] != NULL) 
				ft_memdel(&array->contents[i]);
			i++;
		}
	}
}
