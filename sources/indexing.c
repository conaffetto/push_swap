/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:29:20 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/01 15:38:45 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static uint8_t	check_if_sorted_and_free(int *array_a, size_t n, int *array_b);

/*
* This function copies all integers from stack a to stack b, and sorts the
* latter using a double pivot quick sort function. This sorting procedure's
* objective is to allow the function to assign indices to stack a's integers,
* from zero upwards. For example, if the stack contains the numbers 100, 3 and
* 85, those will be replaced by 2, 0 and 1. This makes the push_swap sorting
* process easier to control, especially when splitting the stack into chunks
* in order to execute the sort, since it allows each chunk to contain all
* consecutive values within a range.
*
* NOTE: stack_b->n remains 0 throughout this function!
* After the ft_memmove() call which copies stack a's array into stack b,
* assign_indices() passes stack b's array with stack a's 'n' as parameters to
* double_pivot_quick_sort(). This might seem odd, but it is done in order to
* avoid assigning to stack_b->n the same value as stack_a->n, only to reset
* stack_b->n to zero just after the indexing and before the splitting process,
* which overwrites stack_b's integers. This is entirely safe however, since we
* know for certain that stack_b contains stack_a->n amount of integers in it.
*
* NOTE: If the stack contains any duplicates, those are detected during the
* quick sort of stack b, returning a true dupliacte_flag value to the present
* function, which then frees the memory of both stacks and handles the error.
*
* Please note that because the indexing process casts the index found into an
* int data type when assiging the corresponding index to a value in stack a,
* this push_swap program accepts up to INT_MAX amount of integers. The terminal
* does not accept more than that anyhow, but if for any future reason one would
* need to make the program accept more than this amount of elements, a possible
* solution would be to replace the INT array's data type to LONG.
*
* Return values are identical to the static check_if_sorted_and_free(), i.e.:
*	1 if the array is already sorted,
*	0 if it is not
*/
uint8_t	assign_indices(int *array_a, int *array_b, size_t n)
{
	uint16_t	duplicate_flag;
	size_t		i;
	size_t		j;

	ft_memmove(array_b, array_a, (n * sizeof(int)));
	duplicate_flag = double_pivot_quick_sort(array_b, n);
	if (duplicate_flag)
	{
		free_both_stacks(&array_a, &array_b);
		invalid_input_found();
	}
	i = 0;
	j = 0;
	while (i < n)
	{
		while (array_a[i] != array_b[j])
			j++;
		array_a[i] = (int) j;
		j = 0;
		i++;
	}
	if (check_if_sorted_and_free(array_a, n, array_b))
		return (1);
	return (0);
}

/*
* At the tail end of assign_indices(), a check is made to see whether the array
* is already sorted. If it is the case, both stacks are freed and it returns 1.
* The 'top' parameter expected by is_sorted_circular_array(), which allows that
* function to know where the 1st element of the array truly is located, is in
* any case zero at this point of the program, and so, 0 is passed instead of
* stack_a->top.
*
* Return values:	1 if the array is already sorted
*					0 if it is not
*/
static uint8_t	check_if_sorted_and_free(int *array_a, size_t n, int *array_b)
{
	if (is_sorted_circular_array(array_a, n, 0))
	{
		free_both_stacks(&array_a, &array_b);
		return (1);
	}
	return (0);
}
