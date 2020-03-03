#include "darray.h"
#include "libft.h"

static int8_t	darray_resize(t_darray *array, size_t newsize)
{
	void	*contents;
	int8_t	ret;

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

/*
** Since array->max is an index,+
*/
int8_t			darray_expand(t_darray *array)
{
	size_t	old_max;
	int8_t	ret;

	ret = SUCCESS;
	old_max = array->max;
	ret = darray_resize(array, array->max + array->expand_rate);
	if (ret == SUCCESS)
		ft_memset(array->contents + old_max, 0, array->expand_rate + 1);
	else
		ft_print_err_failure(FAILED_TO_EXPAND, STD_ERR);
	return (ret);
}

int8_t			darray_contract(t_darray *array)
{
	size_t newsize;

	newsize = (array->end < array->expand_rate) ? array->expand_rate : array->end;
	return (darray_resize(array, newsize + 1));
}
