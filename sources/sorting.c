/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:16:18 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/28 22:57:20 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* This function should only be called if, once the parsing of the arguments is
* complete, there are either a single integer OR two integers in the stack.
* It sorts the stack if necessary, and frees its previously malloc'ed memory.
* If there are two equal integers, it handles that as invalid input.
*/
void	handle_one_or_two_integers(t_stack *stack_a)
{
	if (stack_a->n == 1)
		free_single_stack(&stack_a->array);
	else
	{
		if (*stack_a->array == *(stack_a->array + 1))
		{
			free_single_stack(&stack_a->array);
			invalid_input_found();
		}
		else
		{
			if (*stack_a->array > *(stack_a->array + 1))
				swap_top(stack_a, NULL, 'a');
			free_single_stack(&stack_a->array);
		}
	}
}

/*
* sort_three() simply sorts a stack containing three integers, with the least
* amount of push swap instructions, and displays the instructions employed on
* the screen. At most, two instructions are needed in certain scenarios.
* Needless to say, this function should not be called if there are less (or
* more) than three elements in the stack.
* Since the push swap instruction functions take pointers to both stack a and
* b, sort_three(), which calls those functions, has to take in both of these.
* The '*top' and 'n' arguments are added here for the sake of readability.
*/
void	sort_three(t_stack *stack_a, size_t *top, size_t n, t_stack *stack_b)
{
	if (stack_a->array[*top] < stack_a->array[(*top + 1) % n])
	{
		if (stack_a->array[(*top + 1) % n] > stack_a->array[(*top + 2) % n])
		{
			if (stack_a->array[(*top + 2) % n] < stack_a->array[*top])
				reverse_rotate_stack(stack_a, stack_b, 'a');
			else
				swap_rotate(stack_a, stack_b, 1);
		}
	}
	else
	{
		if (stack_a->array[(*top + 1) % n] < stack_a->array[(*top + 2) % n])
		{
			if (stack_a->array[(*top + 2) % n] > stack_a->array[*top])
				swap_top(stack_a, stack_b, 'a');
			else
				rotate_stack(stack_a, stack_b, 'a');
		}
		else
			swap_rotate(stack_a, stack_b, 2);
	}
}

/*
* a helper function that is used to execute a sequence of two push swap moves.
* scenario = 1: swap and rotate stack A
* scenario = 2: swap and reverse rotate stack A
* scenario = 3: swap and rotate stack B
* scenario = 4: swap and reverse rotate stack B
* NOTE: When calling this function, keep the order of the stacks as they appear
* in the arguments of the prototoype; only the scenario input influences which
* of the stacks will be operated upon.
*/
void	swap_rotate(t_stack *stack_a, t_stack *stack_b, uint8_t scenario)
{
	if (scenario == 1)
	{
		swap_top(stack_a, stack_b, 'a');
		rotate_stack(stack_a, stack_b, 'a');
	}
	else if (scenario == 2)
	{
		swap_top(stack_a, stack_b, 'a');
		reverse_rotate_stack(stack_a, stack_b, 'a');
	}
	else if (scenario == 3)
	{
		swap_top(stack_a, stack_b, 'b');
		rotate_stack(stack_a, stack_b, 'b');
	}
	else
	{
		swap_top(stack_a, stack_b, 'b');
		reverse_rotate_stack(stack_a, stack_b, 'b');
	}
}
