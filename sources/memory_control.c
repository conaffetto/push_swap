/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:57:11 by ykadosh           #+#    #+#             */
/*   Updated: 2025/04/01 15:27:04 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* allocates an integer array of the size given as a parameter
* return values: 0 in case of malloc() failure, 1 in case of success
* NOTE: Size is only passed if it is at least 1, so this function does not
* need to check for ft_calloc()'s return of a pointer pointing at 0
*/
uint8_t	allocate_array(int **array, size_t size)
{
	*array = (int *)ft_calloc(size, sizeof(int));
	if (!*array)
		return (0);
	return (1);
}

/*
* frees the integer array and resets its pointer to NULL (the double pointer
* allows for the address reset to be valid in the caller's scope)
*/
void	free_single_stack(int **array)
{
	free(*array);
	*array = NULL;
}

/*
* frees both stack_a and stack_b, taken in as double pointers, so that they
* may both be safely reset to point to NULL.
* only frees the ones which are not already pointing to NULL
*/
void	free_both_stacks(int **array_a, int **array_b)
{
	if (*array_a)
	{
		free(*array_a);
		*array_a = NULL;
	}
	if (*array_b)
	{
		free(*array_b);
		*array_b = NULL;
	}
}
