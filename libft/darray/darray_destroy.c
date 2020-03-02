#include "darray.h"

void	darray_destroy(t_darray *array)
{
	if (array != NULL)
	{
		if (array->contents != NULL)
			free(array->contents);
		free(array);
	}
}

void	darray_clear_destroy(t_darray *array)
{
	darray_clear(array);
	darray_destroy(array);
}
