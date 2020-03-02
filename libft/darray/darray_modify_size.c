#include "darray.h"

static int8_t	darray_resize(t_array *array, size_t newsize)
{
	int8_t	ret;
	void	*contents;

	ret = FAILURE;
	if (newsize == 0)
		ret = ft_print_err_failure(NEWSIZE_ZERO, STD_ERR);
	else
	{
		array->max = newsize;
		contents = realloc(array->contents, array->max * sizeof(void*));
		if (contents == NULL)
			ret = FAILURE;
		else
			ret = SUCCESS;
	}
	return (ret);
}

int8_t		darray_expand(t_array *array)
{
	size_t old_max;
	int8_t	ret;
	
	ret = SUCCESS;
	old_max = array->max;
    	if ((ret = darray_resize(array, array->max + array->expand_rate)) == FAILURE)
		ret = ft_print_err_failure(FAILED_TO_EXPAND, STD_ERR);
	else
		ft_memset(array->contents + old_max, 0, array->expand_rate + 1);
i	return (ret);
}

int8_t		darray_contract(t_array *array)
{
	size_t newsize;

	newsize = array->end < (int32_t)array->expand_rate ?
		(int32_t)array->expand_rate : array->end;
	return (darray_resize(array, new_size + 1));
}
