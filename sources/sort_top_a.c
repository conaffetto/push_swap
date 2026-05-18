/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_top_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:51:28 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/28 23:23:49 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_top_a(t_stack *stack_a, t_stack *stack_b, size_t top,
				size_t n);
static void	next_more_than_top(t_stack *stack_a, t_stack *stack_b, uint8_t op);
static void	top_more_than_next(t_stack *stack_a, t_stack *stack_b, uint8_t op);

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
void	sort_top_a(t_stack *stack_a, t_stack *stack_b, size_t size)
{
	size_t	top;
	size_t	n;

	top = stack_a->top;
	n = stack_a->n;
	if (size == 2)
		if (stack_a->array[top] > stack_a->array[(top + 1) % n])
			swap_top(stack_a, stack_b, 'a');
	if (size == 3)
		sort_three_top_a(stack_a, stack_b, top, n);
}

/*
* The 'op' variable implemented in sort_three_top_a()'s helper functions is
* simply a flag that is used for each of the six possible sequences of three
* unequal integers.
* Here are the corresponding sequences, represented by the numbers 1, 2 & 3:
*
* op 1: 2, 3, 1
* op 2: 1, 3, 2
*(op 3: 1, 2, 3 - already sorted, since we are on TOP A, so it is ignored)
* op 4: 2, 1, 3
* op 5: 3, 1, 2
* op 6: 3, 2, 1
*/
static void	sort_three_top_a(t_stack *stack_a, t_stack *stack_b, size_t top,
				size_t n)
{
	if (stack_a->array[top] < stack_a->array[(top + 1) % n])
	{
		if (stack_a->array[(top + 1) % n] > stack_a->array[(top + 2) % n])
		{
			if (stack_a->array[(top + 2) % n] < stack_a->array[top])
				next_more_than_top(stack_a, stack_b, 1);
			else
				next_more_than_top(stack_a, stack_b, 2);
		}
	}
	else
	{
		if (stack_a->array[(top + 1) % n] < stack_a->array[(top + 2) % n])
		{
			if (stack_a->array[(top + 2) % n] > stack_a->array[top])
				top_more_than_next(stack_a, stack_b, 4);
			else
				top_more_than_next(stack_a, stack_b, 5);
		}
		else
			top_more_than_next(stack_a, stack_b, 6);
	}
}

static void	next_more_than_top(t_stack *stack_a, t_stack *stack_b, uint8_t op)
{
	if (op == 1)
	{
		rotate_stack(stack_a, stack_b, 'a');
		swap_rotate(stack_a, stack_b, 2);
		swap_top(stack_a, stack_b, 'a');
	}
	else if (op == 2)
	{
		rotate_stack(stack_a, stack_b, 'a');
		swap_rotate(stack_a, stack_b, 2);
	}
}

static void	top_more_than_next(t_stack *stack_a, t_stack *stack_b, uint8_t op)
{
	if (op == 4)
		swap_top(stack_a, stack_b, 'a');
	else if (op == 5)
	{
		rotate_stack(stack_a, stack_b, 'a');
		push(stack_a, stack_b, 'b');
		reverse_rotate_stack(stack_a, stack_b, 'a');
		swap_top(stack_a, stack_b, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (op == 6)
	{
		swap_rotate(stack_a, stack_b, 1);
		swap_rotate(stack_a, stack_b, 2);
		swap_top(stack_a, stack_b, 'a');
	}
}
