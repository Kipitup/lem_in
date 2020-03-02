
#include "darray.h"
#include "libft.h"

void	darray_clear(t_darray *array)
{
	int32_t i;

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
