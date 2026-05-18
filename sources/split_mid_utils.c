/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:03:37 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/26 16:51:01 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static uint8_t	mid_to_max(t_stack *stack_a, t_stack *stack_b, size_t *size,
					int8_t position_flag);
static void		mid_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size,
					int8_t position_flag);
static void		mid_to_min(t_stack *stack_a, t_stack *stack_b, size_t *size,
					int8_t position_flag);

void	split_mid_from_top_b(t_map *map, t_stack *stack_a, t_stack *stack_b)
{
	size_t		initial_n;
	int32_t		low_pivot;
	int32_t		high_pivot;
	uint16_t	truncation_size;

	initial_n = init_split(map, &map->chunk_mid, &low_pivot, &high_pivot);
	truncation_size = 0;
	while (initial_n)
	{
		if (stack_b->array[stack_b->top] >= high_pivot)
			truncation_size += mid_to_max(stack_a, stack_b,
					&map->chunk_max.size, 0);
		else if (stack_b->array[stack_b->top] >= low_pivot)
			mid_to_mid(stack_a, stack_b, &map->chunk_mid.size, 0);
		else
			mid_to_min(stack_a, stack_b, &map->chunk_min.size, 0);
		initial_n--;
	}
	high_pivot += truncation_size;
	update_chunk_limits(map, low_pivot, high_pivot);
}

void	split_mid_from_bottom_a(t_map *map, t_stack *stack_a, t_stack *stack_b)
{
	size_t		initial_n;
	int32_t		low_pivot;
	int32_t		high_pivot;
	uint16_t	truncation_size;

	initial_n = init_split(map, &map->chunk_mid, &low_pivot, &high_pivot);
	truncation_size = 0;
	while (initial_n)
	{
		reverse_rotate_stack(stack_a, stack_b, 'a');
		if (stack_a->array[stack_a->top] >= high_pivot)
			truncation_size += mid_to_max(stack_a, stack_b,
					&map->chunk_max.size, 1);
		else if (stack_a->array[stack_a->top] >= low_pivot)
			mid_to_mid(stack_a, stack_b, &map->chunk_mid.size, 1);
		else
			mid_to_min(stack_a, stack_b, &map->chunk_min.size, 1);
		initial_n--;
	}
	high_pivot += truncation_size;
	update_chunk_limits(map, low_pivot, high_pivot);
}

/*
* position_flag = 0: means that chunk MID is located at TOP B
* position_flag = 1: means that chunk MID is located at BOTTOM A (but a first
* reverse rotation is executed just before this function call, so the top
* integer of MID is located at TOP A)
*/
static uint8_t	mid_to_max(t_stack *stack_a, t_stack *stack_b, size_t *size,
					int8_t position_flag)
{
	if (position_flag == 0)
		push(stack_b, stack_a, 'a');
	(*size)++;
	if (*size < 4)
		return (early_sort(stack_a, size, stack_b));
	return (0);
}

/*
* position_flag = 0: means that chunk MID is located at TOP B
* position_flag = 1: means that chunk MID is located at BOTTOM A (but a first
* reverse rotation is executed just before this function call, so the top
* integer of MID is located at TOP A)
*/
static void	mid_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size,
				int8_t position_flag)
{
	if (position_flag == 0)
	{
		push(stack_b, stack_a, 'a');
		rotate_stack(stack_a, stack_b, 'a');
	}
	else
		push(stack_a, stack_b, 'b');
	(*size)++;
}

/*
* position_flag = 0: means that chunk MID is located at TOP B
* position_flag = 1: means that chunk MID is located at BOTTOM A (but a first
* reverse rotation is executed just before this function call, so the top
* integer of MID is located at TOP A)
*/
static void	mid_to_min(t_stack *stack_a, t_stack *stack_b, size_t *size,
				int8_t position_flag)
{
	if (position_flag == 1)
		push(stack_a, stack_b, 'b');
	rotate_stack(stack_a, stack_b, 'b');
	(*size)++;
}
