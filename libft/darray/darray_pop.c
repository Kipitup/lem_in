
#include "darray.h"
#include "libft.h"

void	*darray_pop(t_darray *array)
{
	void	*element;

	element = NULL;
	if (array->end - 1 <= 0)
	{
		element = darray_remove(array, array->end - 1);
		if (element != NULL)
		{
			array->end--;
			if ((array->end > array->expand_rate) && (array->end % array->expand_rate))
				darray_contract(array);
		}
	}
	else
		ft_print_err_null(FAILED_TO_POP, STD_ERR);
	return (element);
}
