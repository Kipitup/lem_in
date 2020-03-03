
#include "darray.h"
#include "libft.h"

void	*darray_pop(t_darray *array)
{
	void	*element;
	
	if (array->end - 1 <= 0)
		ft_print_err_void(FAILED_TO_POP, STD_ERR);
	element = darray_remove(array, array->end - 1);
	if (element != NULL)
	{
		array->end--;
		if (array->end > (int)array->expand_rate
				&& array->end % array->expand_rate)
			darray_contract(array);
	}
	return (element);
}
