#include "darray.h"
#include "libft.h"

int8_t	darray_push(t_darray *array, void *element)
{
	int8_t	ret;

	if (array != NULL)
	{
		ret = FAILURE;
		array->end++;
		if (array->end >= array->max)
			ret = darray_expand(array);
		else 
			ret = 0;
		array->contents[array->end] = element;
		return (ret);
	}
	else
		return(ft_print_err_failure(ARRAY_IS_NULL, STD_ERR));
}	
