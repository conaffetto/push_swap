/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   early_sort_optimization.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:00:26 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/26 23:01:56 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static uint8_t	is_within_range(size_t size, int *array, size_t n, size_t top);

/*
* Early sort optimization: Whenever integers are sent to the top of stack A
* during the splitting of a chunk, if the first one, two, or three integers are
* within sorting range with the integer of the chunk below them, then those are
* being sorted immediately through early_sort(). The size of the chunk is then
* reduced accordingly, and the next batch of up to three elements are compared
* to the lastly updated top of the stack. This prevents integers - that are
* sent to the top of stack A and find themselves either already sorted or very
* close to being sorted - from being sent around the stacks, potentially
* several times, only to be sorted much later.
*/
uint8_t	early_sort(t_stack *stack_a, size_t *size, t_stack *stack_b)
{
	uint8_t	flag;

	flag = is_within_range(*size, stack_a->array, stack_a->n, stack_a->top);
	if (flag == 1)
	{
		(*size)--;
		return (1);
	}
	if (flag == 2)
	{
		sort_top_a(stack_a, stack_b, 2);
		*size -= 2;
		return (2);
	}
	if (flag == 3)
	{
		sort_top_a(stack_a, stack_b, 3);
		*size -= 3;
		return (3);
	}
	return (0);
}

static uint8_t	is_within_range(size_t size, int *array, size_t n, size_t top)
{
	int32_t	previous_top_value;
	int32_t	diff_1;
	int32_t	diff_2;

	previous_top_value = array[(top + size) % n];
	diff_1 = previous_top_value - array[top];
	if (size == 1 && diff_1 == 1)
		return (1);
	else
	{
		diff_2 = previous_top_value - array[(top + 1) % n];
		if (size == 2
			&& (diff_1 == 1 || diff_1 == 2)
			&& (diff_2 == 1 || diff_2 == 2))
			return (2);
		else if (size == 3
			&& diff_1 >= 1 && diff_1 <= 3
			&& diff_2 >= 1 && diff_2 <= 3)
		{
			diff_1 = previous_top_value - array[(top + 2) % n];
			if (diff_1 >= 1 && diff_1 <= 3)
				return (3);
		}
	}
	return (0);
}
