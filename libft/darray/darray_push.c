#include "darray.h"

int8_t	darray_push(t_darray *array, void *element)
{
	int8_t	ret;

	ret = FAILURE;
	array->contents[array->end] = element;
	array->end++;
	if (darray_end(array) >= darray_max(array))
		ret = darray_expand(array);
	else 
		ret = 0;
	return (ret);
	
}
