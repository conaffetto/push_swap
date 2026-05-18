/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:21:26 by ykadosh           #+#    #+#             */
/*   Updated: 2025/02/27 14:21:49 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* simply writes "Error" followed by a newline to the standard error and exits
* with exit status 2.
* If write() fails for any reason, exit status is: 3
*/
void	invalid_input_found(void)
{
	if (write(2, "Error\n", 6) == -1)
		exit (3);
	exit (2);
}

/*
* swaps the two integers passed as parameters
*/
void	ft_swap(int *x, int *y)
{
	int	temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

/*
* returns true if the circular integer array, passed as an argument, is sorted
* in ascending order, and false if it is not.
* The 'top' variable represents the offset of the circular array's beginning.
* This function does not handle duplicates, since it is only called after
* having handled duplicate integers as an error (as is required by the current
* push_swap program).
*/
uint8_t	is_sorted_circular_array(int *array, size_t n, size_t top)
{
	size_t	i;

	i = 0;
	while (i + 1 < n && array[top] < array[(top + 1) % n])
	{
		top = (top + 1) % n;
		i++;
	}
	if (i + 1 == n)
		return (1);
	else
		return (0);
}
