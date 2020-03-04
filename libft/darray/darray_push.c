#include "darray.h"
#include "libft.h"

int8_t	darray_push(t_darray *array, void *element)
{
	int8_t	ret;

	ret = SUCCESS;
	if (array != NULL)
	{
		array->end++;
		if (array->end >= array->max)
			ret = darray_expand(array);
		if (ret == SUCCESS)
			array->contents[array->end] = element;
	}
	else
		ret = ft_print_err_failure(ARRAY_IS_NULL, STD_ERR);
	return (ret);
}
