#include "darray.h"
#include "libft.h"

int8_t	darray_push(t_darray *array, void *element)
{
	int8_t	ret;

	ret = FAILURE;
	array->contents[array->end] = element;
	array->end++;
	if (array->end >= array->max)
		ret = darray_expand(array);
	else 
		ret = 0;
	return (ret);
	
}
