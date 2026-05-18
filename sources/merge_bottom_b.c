/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_bottom_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:53:13 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/28 22:53:29 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_three_bottom_b(t_stack *stack_a, t_stack *stack_b,
				size_t top, size_t n);
static void	when_top_smaller(t_stack *stack_a, t_stack *stack_b, uint8_t opt);
static void	compare_ints_and_sort(t_stack *stack_a, t_stack *stack_b);
static void	when_top_bigger(t_stack *stack_a, t_stack *stack_b, uint8_t opt);

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
void	merge_bottom_b(t_stack *stack_a, t_stack *stack_b, size_t size)
{
	reverse_rotate_stack(stack_a, stack_b, 'b');
	if (size == 1)
		push(stack_b, stack_a, 'a');
	if (size == 2)
	{
		if (stack_b->array[(stack_b->top)]
			< stack_b->array[(stack_b->n + stack_b->top - 1) % stack_b->n])
		{
			reverse_rotate_stack(stack_a, stack_b, 'b');
			push(stack_b, stack_a, 'a');
			push(stack_b, stack_a, 'a');
		}
		else
		{
			push(stack_b, stack_a, 'a');
			reverse_rotate_stack(stack_a, stack_b, 'b');
			push(stack_b, stack_a, 'a');
		}
	}
	if (size == 3)
		sort_three_bottom_b(stack_a, stack_b, stack_b->top, stack_b->n);
}

/*
* The indexing here might appear strange: this is because sort_three_bottom_b()
* sorts the top three integers of the chunk positioned in BOTTOM B into the top
* of stack A, which means that the indices are inversed: the 'top' of bottom B
* is actually at the very bottom of stack B, while the 2nd and 3rd integers
* are, respectively, one and two indices before the last index of the stack.
* Since all scenarios of merge_bottom_b() begin by a reverse rotate of stack B,
* that reverse rotation is executed at the very beginning of merge_bottom_b(),
* causing the last index (which is bottom B's top) to move to the top of the
* stack. From there, the comparisons are made between that integer and those
* located 'behind' it, i.e. the last and before last indices of the stack.
*
* The 'opt' variable implemented in sort_three_bottom_b()'s helper functions is
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
static void	sort_three_bottom_b(t_stack *stack_a, t_stack *stack_b,
				size_t top, size_t n)
{
	if (stack_b->array[top] < stack_b->array[(n + top - 1) % n])
	{
		if (stack_b->array[(n + top - 1) % n]
			> stack_b->array[(n + top - 2) % n])
		{
			if (stack_b->array[(n + top - 2) % n] < stack_b->array[top])
				when_top_smaller(stack_a, stack_b, 1);
			else
				when_top_smaller(stack_a, stack_b, 2);
		}
		else
			when_top_smaller(stack_a, stack_b, 3);
	}
	else
	{
		if (stack_b->array[(n + top - 1) % n]
			< stack_b->array[(n + top - 2) % n])
			compare_ints_and_sort(stack_a, stack_b);
		else
			when_top_bigger(stack_a, stack_b, 6);
	}
}

static void	when_top_smaller(t_stack *stack_a, t_stack *stack_b, uint8_t opt)
{
	if (opt == 1)
	{
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 2)
	{
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 3)
	{
		reverse_rotate_stack(stack_a, stack_b, 'b');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
}

static void	compare_ints_and_sort(t_stack *stack_a, t_stack *stack_b)
{
	size_t	n;
	size_t	top;

	n = stack_b->n;
	top = stack_b->top;
	if (stack_b->array[(n + top - 2) % n] > stack_b->array[top])
		when_top_bigger(stack_a, stack_b, 4);
	else
		when_top_bigger(stack_a, stack_b, 5);
}

static void	when_top_bigger(t_stack *stack_a, t_stack *stack_b, uint8_t opt)
{
	if (opt == 4)
	{
		reverse_rotate_stack(stack_a, stack_b, 'b');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		swap_top(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 5)
	{
		push(stack_b, stack_a, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		push(stack_b, stack_a, 'a');
	}
	else if (opt == 6)
	{
		push(stack_b, stack_a, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'b');
		push(stack_b, stack_a, 'a');
	}
}
