/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_instructions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:32:21 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/18 20:34:24 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_write_failure(t_stack *stack_a, t_stack *stack_b);

/*
* swaps the top integer of a stack with the one below it, if the stack contains
* at least two integers. The third argument is used to identify which stack is
* to be operated upon. Three options are available:
* - pass character 'a' to swap the top of stack a, and display "sa"
* - pass character 'b' to swap the top of stack b and display "sb"
* - pass character 's' to operate on both stacks, and display "ss"
* Those messages are all followed by a newline character.
* Please note that this function - like all other functions below it, dedicated
* to the execution of the push swap instructions - handles all eventual write()
* failures, by freeing the malloc'ed stacks and exiting the program with exit
* status 3.
*/
void	swap_top(t_stack *stack_a, t_stack *stack_b, char id)
{
	if (id == 'a' && stack_a->n > 1)
	{
		ft_swap(stack_a->array + stack_a->top,
			stack_a->array + ((stack_a->top + 1) % stack_a->n));
		if (write(1, "sa\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 'b' && stack_b->n > 1)
	{
		ft_swap(stack_b->array + stack_b->top,
			stack_b->array + ((stack_b->top + 1) % stack_b->n));
		if (write(1, "sb\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 's' && stack_a->n > 1 && stack_b->n > 1)
	{
		ft_swap(stack_a->array + stack_a->top,
			stack_a->array + ((stack_a->top + 1) % stack_a->n));
		ft_swap(stack_b->array + stack_b->top,
			stack_b->array + ((stack_b->top + 1) % stack_b->n));
		if (write(1, "ss\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
}

/*
* rotates the top integer of a stack, placing it at the very bottom; the second
* integer thus becomes the top of the stack. In this program, since the stacks
* are implemented as circular arrays, this rotation is achieved by using a
* 'top' variable - indicating the stack's top integer's offset position
* relative to the 0'th index of the array - which the present function simply
* increments by one (using a modulo calculation against the number of elements
* currently in the stack, ensuring that the incrementation would wrap around
* to the 0'th index of the array when necessary).
* Just like swap_top(), rotate_stack() allows to operate on stack a, stack b
* or both, if they contain at least two integers. According to the operation
* executed, this function prints "ra", "rb" or "rr", followed by a newline.
* Please refer to swap_top()'s comments at the top of this file for details
* regarding the handling of eventual failure of write().
* Do not invert the order of the stacks, rather, use 'a' for the id argument
* when wishing to rotate stack a, and use 'b' to indicate a rotation request
* for stack b.
*/
void	rotate_stack(t_stack *stack_a, t_stack *stack_b, char id)
{
	if (id == 'a' && stack_a->n > 1)
	{
		stack_a->top = (stack_a->top + 1) % stack_a->n;
		if (write(1, "ra\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 'b' && stack_b->n > 1)
	{
		stack_b->top = (stack_b->top + 1) % stack_b->n;
		if (write(1, "rb\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 's' && stack_a->n > 1 && stack_b->n > 1)
	{
		stack_a->top = (stack_a->top + 1) % stack_a->n;
		stack_b->top = (stack_b->top + 1) % stack_b->n;
		if (write(1, "rr\n", 3) == -1)
			handle_write_failure(stack_a, stack_b);
	}
}

/*
* rotates the bottom integer of a stack, placing it at the very top; Since the
* stacks are implemented as circular arrays in the current program, the reverse
* rotation is achieved by decrementing the stack's 'top' offset by one (using a
* modulo calculation against the stack's n variable, ensuring that the offset
* would wrap around to the array's last index when necessary).
* Just like swap_top() and rotate_stack(), reverse_rotate_swap() allows to
* operate on stack a, stack b or both, if they contain at least two integers.
* According to the operation executed, this function prints "rra", "rrb" or
* "rrr", all followed by a newline character.
* Please refer to swap_top()'s comments for details regarding the handling of
* eventual failure of write().
* Do not invert the order of the stacks, rather, use 'a' for the id argument
* when wishing to reverse rotate stack a, and use 'b' to indicate a rotation
* request for stack b.
*/
void	reverse_rotate_stack(t_stack *stack_a, t_stack *stack_b, char id)
{
	if (id == 'a' && stack_a->n > 1)
	{
		stack_a->top = (stack_a->n + stack_a->top - 1) % stack_a->n;
		if (write(1, "rra\n", 4) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 'b' && stack_b->n > 1)
	{
		stack_b->top = (stack_b->n + stack_b->top - 1) % stack_b->n;
		if (write(1, "rrb\n", 4) == -1)
			handle_write_failure(stack_a, stack_b);
	}
	if (id == 's' && stack_a->n > 1 && stack_b->n > 1)
	{
		stack_a->top = (stack_a->n + stack_a->top - 1) % stack_a->n;
		stack_b->top = (stack_b->n + stack_b->top - 1) % stack_b->n;
		if (write(1, "rrr\n", 4) == -1)
			handle_write_failure(stack_a, stack_b);
	}
}

/*
* pushes the top integer of 'origin' stack to the top of 'target' stack, if
* 'origin' has any integer in it. Please be mindful of the order of the
* arguments when calling this function. The 'id' argument should be 'a' when
* pushing from stack b to stack a, or 'b', when intending to do the opposite.
* This function also adjusts the 'top' offset of each stack (if needed) and
* updates their number of elements, as well.
* prints: "pa" when pushing from b to a, and "pb" when pushing from a to b -
* both followed by a newline character.
* Please refer to the comments at the top of the file for details regarding
* handling of the eventual failure of write().
*/
void	push(t_stack *origin, t_stack *target, char id)
{
	if (origin->n)
	{
		target->n++;
		if (target->top < target->n - 1)
			ft_memmove(target->array + target->top + 1,
				target->array + target->top,
				sizeof(int) * (target->n - target->top - 1));
		*(target->array + target->top) = *(origin->array + origin->top);
		origin->n--;
		if (origin->top < origin->n)
			ft_memmove(origin->array + origin->top,
				origin->array + origin->top + 1,
				sizeof(int) * (origin->n - origin->top));
		else
			origin->top = 0;
		if (id == 'a')
			if (write(1, "pa\n", 3) == -1)
				handle_write_failure(origin, target);
		if (id == 'b')
			if (write(1, "pb\n", 3) == -1)
				handle_write_failure(origin, target);
	}
}

/*
* frees both stacks, resets their array pointers to NULL, and exits
*/
static void	handle_write_failure(t_stack *stack_a, t_stack *stack_b)
{
	free_both_stacks(&stack_a->array, &stack_b->array);
	exit (3);
}
