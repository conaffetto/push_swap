/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_top_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:37:18 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/28 18:05:38 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_top_b(t_stack *stack_a, t_stack *stack_b, size_t top,
				size_t n);
static void	if_2nd_is_greater(t_stack *stack_a, t_stack *stack_b, uint8_t opt);
static void	if_1st_is_greater(t_stack *stack_a, t_stack *stack_b, uint8_t opt);

/*
* The current program splits the stacks into chunks in order to speed up the
* process of sorting stack A's integers. Thanks to the reverse rotation action
* that push_swap allows for, the chunks are organised in four different
* positions:
* 1. "TOP A": the top of stack a
* 2. "BOTTOM A": the bottom of stack a
* 3. "TOP B": the top of stack b
* 4. "BOTTOM B": the bottom of stack b
*
* The base case that determines when NOT to split a chunk into sub-chunks
* anymore is if it contains less than four integers. When that case is reached,
* the chunk's remaining 1, 2 or 3 integers have to be sorted back into the top
* of stack A. Note that those integers may not be the ONLY ones present in the
* stack: Therefore, the following function compares the integers remaining in
* the chunk, and executes the least amount of push_swap instructions that sorts
* them into the top of stack a, while taking into account that there may be
* other elements within the stack in which the chunk is located.
*
* 'size' is the number of integers that are left in the chunk, and that are
* going to be sorted by this function.
* The function should only be called if 'size' is between the range of 1 and 3.
*/
void	merge_top_b(t_stack *stack_a, t_stack *stack_b, size_t size)
{
	size_t	top;
	size_t	n;

	top = stack_b->top;
	n = stack_b->n;
	if (size == 1)
		push(stack_b, stack_a, 'a');
	if (size == 2)
	{
		if (stack_b->array[top] < stack_b->array[(top + 1) % n])
			swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	if (size == 3)
		sort_three_top_b(stack_a, stack_b, top, n);
}

/*
* The 'opt' variable implemented in sort_three_top_b()'s helper functions is
* simply a flag that is used for each of the six possible sequences of three
* unequal integers.
* Here are the corresponding sequences, represented by the numbers 1, 2 & 3:
*
* opt 1: 2, 3, 1
* opt 2: 1, 3, 2
* opt 3: 1, 2, 3
* opt 4: 2, 1, 3
* opt 5: 3, 1, 2
* opt 6: 3, 2, 1
*/
static void	sort_three_top_b(t_stack *stack_a, t_stack *stack_b, size_t top,
				size_t n)
{
	if (stack_b->array[top] < stack_b->array[(top + 1) % n])
	{
		if (stack_b->array[(top + 1) % n] > stack_b->array[(top + 2) % n])
		{
			if (stack_b->array[(top + 2) % n] < stack_b->array[top])
				if_2nd_is_greater(stack_a, stack_b, 1);
			else
				if_2nd_is_greater(stack_a, stack_b, 2);
		}
		else
			if_2nd_is_greater(stack_a, stack_b, 3);
	}
	else
	{
		if (stack_b->array[(top + 1) % n] < stack_b->array[(top + 2) % n])
		{
			if (stack_b->array[(top + 2) % n] > stack_b->array[top])
				if_1st_is_greater(stack_a, stack_b, 4);
			else
				if_1st_is_greater(stack_a, stack_b, 5);
		}
		else
			if_1st_is_greater(stack_a, stack_b, 6);
	}
}

static void	if_2nd_is_greater(t_stack *stack_a, t_stack *stack_b, uint8_t opt)
{
	if (opt == 1)
	{
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 2)
	{
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 3)
	{
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'a');
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'a');
	}
}

static void	if_1st_is_greater(t_stack *stack_a, t_stack *stack_b, uint8_t opt)
{
	if (opt == 4)
	{
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 5)
	{
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 6)
	{
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
}
