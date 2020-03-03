/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_darray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 09:58:13 by fkante            #+#    #+#             */
/*   Updated: 2020/03/03 20:04:02 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "darray.h"
#include "libft.h"

int8_t	test_push_pop(t_darray *array)
{
    int32_t i;
	int32_t	*val;

	i = 0;
	while (i < 10)
	{
		val = darray_new(array);
		*val = i; 
		darray_push(array, val);
		i++;
	}
	ft_printf("max value index %d\n", array->end);
	for (i = 0; i <= array->end; i++)
		ft_printf("content = %d\n", *((int*)array->contents[i]));
	ft_printf("------------ pop -----------\n");
	i = 10;
	while (i > 0)
	{
        val = darray_pop(array);
		ft_printf("popped = %d\n", *val);
		if (val == NULL)
			return (ft_print_err_failure("pop shouldn't be NULL", STD_ERR));
        ft_memdel((void**)&val);
		i--;
    }
   return (TRUE);
}

int8_t	test_expand_contract(t_darray *array, int *val1, int *val2)
{
    int old_max;

	old_max = array->max;
    darray_expand(array);
	ft_printf("newsize after expand = %d\n", array->max);
	if (array->max != old_max + array->expand_rate)
		return(ft_print_err_failure("wrong size after expand", STD_ERR));
	old_max = array->max;
    darray_expand(array);
	ft_printf("newsize after second expand = %d\n", array->max);
	if (array->max != old_max + array->expand_rate)
		return(ft_print_err_failure("wrong size after expand", STD_ERR));
   	darray_contract(array);
	ft_printf("newsize after contract = %d\n", array->max);
	if (array->max != array->expand_rate)
		return(ft_print_err_failure("Should stay at the expand_rate at least", STD_ERR));
   	darray_contract(array);
	ft_printf("newsize after second contract = %d\n\n", array->max);
	if (array->max != array->expand_rate)
		return(ft_print_err_failure("Should stay at the expand_rate at least", STD_ERR));
    return (TRUE);
}

int8_t	test_remove(t_darray *array, int *val1, int *val2)
{
    int *val_removed = darray_remove(array, 0);

	if (val_removed == NULL)
		return (ft_print_err_failure("removed should not be NULL", STD_ERR));
    if (*val_removed != *val1)
		return (ft_print_err_failure("val_removed should be == to val1", STD_ERR));
	if (darray_get(array, 0) != NULL)
		return (ft_print_err_failure("array->content[0] should be NULL", STD_ERR));
	ft_memdel((void**)&val_removed);
	
	val_removed = darray_remove(array, 1);
	if (val_removed == NULL)
		return (ft_print_err_failure("removed should not be NULL", STD_ERR));
    if (*val_removed != *val2)
		return (ft_print_err_failure("val_removed should be == to val2", STD_ERR));
	if (darray_get(array, 1) != NULL)
		return (ft_print_err_failure("array->content[1] should be NULL", STD_ERR));
	ft_memdel((void**)&val_removed);
	return (TRUE);
}

void	test_destroy(t_darray **array)
{
	darray_destroy(array);
}

int8_t	test_get(t_darray *array, int *val1, int *val2)
{
	ft_printf("darray get 0 = %d\n", *((int*)darray_get(array, 0)));
	if (darray_get(array, 0) != val1)
		return (ft_print_err_failure("Wrong first value.", STD_ERR));
	ft_printf("darray get 1 = %d\n\n", *((int*)darray_get(array, 1)));
	if (darray_get(array, 1) != val2)
		return (ft_print_err_failure("Wrong second value.", STD_ERR));
	return (TRUE);
}

int8_t	test_new_and_set(t_darray *array, int *val1, int *val2)
{
	int	*new_element1;
	int	*new_element2;
	
	ft_printf("\nval1\t= %d\tval2\t= %d\n\n", *val1, *val2);
	new_element1 = darray_new_and_set(array, 0, val1);
	new_element2 = darray_new_and_set(array, 1, val2);
	ft_printf("content[0]\t= %d\n", *((int*)array->contents[0]));
	ft_printf("content[1]\t= %d\n\n", (int)new_element2[0]);
	test_get(array, val1, val2);
	test_expand_contract(array, val1, val2);
	test_push_pop(array);

//	ft_memdel((void**)&new_element1);
//	ft_memdel((void**)&new_element2);
	return (TRUE);
}

int8_t	test_create(void)
{
	t_darray	*array = NULL;
	static int	val1[] = {68};
	static int	val2[] = {42};
	array = darray_create(sizeof(int), 100);

	if (array == NULL)
		return (ft_print_err_failure("darray_create failed.", STD_ERR));
	if (array->contents == NULL)
		return (ft_print_err_failure("contents are wrong in darray", STD_ERR));
	if (array->end != 0)
		return (ft_print_err_failure("end isn't at the right spot", STD_ERR));
	if (array->element_size != sizeof(int))
		return (ft_print_err_failure("element size is wrong.", STD_ERR));
	if (array->max != 100)
		return (ft_print_err_failure("wrong max length on initial size", STD_ERR));

	ft_printf("\n{c_green}Dynamic array created{c_end}\n");

	ft_printf("\n--- make and set new elements ---\n");
	test_new_and_set(array, val1, val2);
	test_destroy(&array);
	return (TRUE);
}

int	main(void)
{
	ft_printf("------ Dynamic array tests ------\n");
	test_create();
	ft_printf("--------------- END -------------\n");
	return (0);
}
