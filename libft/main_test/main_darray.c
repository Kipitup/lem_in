#include "darray.h"
#include "libft.h"

int8_t	test_create(t_darray *array)
{
	array = t_darray_create(sizeof(int), 100);
	if (array == NULL)
	{
		ft_print_err_void("darray_create failed.", STD_ERR);
		return (FAILURE);
	}
	if (array->contents == NULL)
	{
		ft_print_err_void("contents are wrong in darray", STD_ERR);
		return (FAILURE);
	}
	if (array->end != 0)
	{
		ft_print_err_void("end isn't at the right spot", STD_ERR);
		return (FAILURE);
	}
	if (array->element_size != sizeof(int))
	{
		ft_print_err_void("element size is wrong.", STD_ERR);
		return (FAILURE);
	}
	if (array->max != 100)
	{
		ft_print_err_void("wrong max length on initial size", STD_ERR);
		return (FAILURE);
	}
	return (TRUE);
}

void	test_destroy(t_darray *array)
{
	darray_destroy(array);
}

int8_t	test_new(t_darray *array, int val1, int val2)
{
	val1 = darray_new(array);
	if (val1 == NULL)
	{
		ft_print_err_void("failed to make a new element", STD_ERR);
		return (FAILURE);
	}
	val2 = darray_new(array);
	if (val2 == NULL)
	{
		ft_print_err_void("failed to make a new element", STD_ERR);
		return (FAILURE);
	}
	return (TRUE);
}

int8_t	test_set(t_darray *array, int val1, int val2)
{
	darray_set(array, 0, val1);
	darray_set(array, 1, val2);
	return (NULL);
}

int8_t	test_get(t_darray *array, int val1, int val2)
{
	if (darray_get(array, 0) != val1)
	{
		ft_print_err_void("Wrong first value.", STD_ERR);
		return (FAILURE);
	}
	if (darray_get(array, 1) != val2)
	{	
		ft_print_err_void("Wrong second value.", STD_ERR);
		return (FAILURE);
	}
	return (SUCCESS);
}


int	main(int ac, char **av)
{
	static t_darray	*array = NULL;
	static int	*val1 = NULL;
	static int	*val2 = NULL;

	ft_printf("--- Dynamic array tests ---\n");
	ft_printf("create darray = %d\n", test_create(array));
	test_destroy(array);
	ft_printf("make new elements = %d\n", test_new(array, &val1, &val2));
	ft_printf("elements have been set = %d\n", test_set(array, &val1, &val2));
	ft_printf("elements are at the right spot = %d\n", test_get(array, &val1, &val2));
	return (0);
}
