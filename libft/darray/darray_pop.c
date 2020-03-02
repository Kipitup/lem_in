
#include "darray.h"

void	*darray_pop(t_array *array)
{
	void	*element = DArray_remove(array, array->end - 1);

	if (array->end - 1 <= 0)
		ft_print_err_void(FAILED_TO_POP, STD_ERR);
	element = darray_remove(array, array->end -1);
	if (element != NULL)
	{
		array->end--;
		if (darray_end(array) > (int)array->expand_rate
				&& darray_end(array) % array->expand_rate)
			darray_contract(array);
	}
	return (element);
}
