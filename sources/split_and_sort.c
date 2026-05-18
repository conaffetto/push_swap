/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:40:22 by ykadosh           #+#    #+#             */
/*   Updated: 2025/04/01 15:14:54 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_map	split_max(t_stack *stack_a, t_stack *stack_b, t_map map);
static void		sort_chunk_max(t_stack *stack_a, t_stack *stack_b, t_map *map);
static t_map	split_mid(t_stack *stack_a, t_stack *stack_b, t_map map);
static t_map	split_min(t_stack *stack_a, t_stack *stack_b, t_map map);

/*
* The algorithm implemented here is an alternative version of the double pivot
* quick sort, which is used earlier in the program in order to assign indices
* to the integers provided to the stack. This version designates two pivots
* within the range of the array, which would split it into three chunks,
* roughly equal in size.
* All values greater than or equal to the high pivot are sent to chunk "MAX";
* all values greater than or equal to the low pivot (but smaller than the
* aforementioned high pivot) are sent to chunk "MID";
* and the remaining values (i.e. all values smaller than the low pivot) are
* sent to chunk "MIN".
* This splitting process is then done recursively for each new chunk created by
* a split, until all of its elements are distributed in the new subchunks.
* Before splitting a chunk, however, if it has less than four elements (i.e. if
* its size is smaller than or equal to three but bigger than 0), those elements
* are sorted right away into the top of stack A. In order to ensure that the
* recursion is executed properly, this program uses the "map" struct to keep
* track of each and every chunk's properties, such as their smallest value
* (min_v), greatest value (max_v), the quantity of elements they hold (size),
* and... their position.
*
* Why their position, one might ask?
* Well, since the push_swap program can employ two stacks to sort the integers,
* and since it allows for 'rotation' and 'reverse rotation' of the top element
* of each stack, it is rather easy to imagine a grand total of FOUR stacks: one
* at the top of stack A and one at the top of stack B, of course, but also one
* stack at each of the stacks' bottom parts.
*
* Each chunk can be located in two distinct positions, because once it is
* being split, it HAS to be emptied - and thus, moved elsewhere.
* The mapping of the chunks' positions is as follows:
* Chunk MAX positions: TOP A or BOTTOM A
* Chunk MID positions: TOP B or BOTTOM A
* Chunk MIN positions: BOTTOM B or TOP B
* When chunk MAX is being split:
*	- the new chunk MAX is generated at BOTTOM A (or at TOP A if it is already
*	at BOTTOM A). If, however, the current chunk MAX is located at TOP A,
*	and it is being split into three, but the new chunk MAX is the ONLY chunk
*	present in stack A, then MAX's position remains TOP A (see further
*	comments regarding optimizations (* see optimization commments further
*	down, n. 2 regarding "decoy"*).
*	- the new chunk MID is generated at TOP B
*	- the new chunk MIN is generated at BOTTOM B
*
* When chunk MID is being split:
*	- if the MID chunk being split is located at TOP B, the new chunk MID is
*	generated at BOTTOM A, and vice versa: if the MID chunk being split is
*	located at BOTTOM A, the new MID is generated at TOP B.
*	- the new chunk MAX is generated at TOP A
*	- the new chunk MIN is generated at BOTTOM B
*
* When chunk MIN is being split:
*	- if the MIN chunk being split is located at BOTTOM B, the new chunk MIN is
*	generated at TOP B, and vice versa, if the current chunk MIN is located at
*	TOP B, the new MIN is created at BOTTOM B. The only 'decoy' exception is
*	if the current MIN is at TOP B, but it is the ONLY chunk present in that
*	stack (meaning new MIN's size == stack_b->n), then the new location of MIN
*	remains TOP B (* see optimization commments further on, n. 2*).
*	- the new chunk MAX is generated at TOP A
*	- the new chunk MID is generated at BOTTOM B
*
* NOTE: There are three main optimization elements that are implemented here,
* to reduce the number of push_swap instructions required for the sorting:
* 1. Small chunks: If a chunk contains less than 9 integers, the program avoids
* splitting into three, and only splits it into MAX and MID chunks. This is
* done in order to mitigate the quantity of push_swap instructions, because
* sending values to chunk MIN, often located at position BOTTOM B, involves
* extra rotations and reverse rotations, which are not very beneficial when the
* chunk is small.
*
* 2*. MAX and MIN acting as a 'decoy': If chunk MAX or chunk MIN are the only
* chunks present within their stack, it is not necessary to tell the program
* that they are positioned at the bottom of the stack. Rather, on the next call
* to split (or sort) them, the program will treat them as located at the TOP of
* their relevant stack. This mitigates the amount of reverse rotations, which
* is a requisite when a chunk is positioned at the bottom.
*
* 3. Early sort optimization: Whenever integers are sent to the top of stack
* A during the splitting of a chunk, if the first one, two, or three integers
* are within sorting range with the integer of the chunk below them, then those
* are being sorted immediately through early_sort(). The size of the chunk is
* then reduced accordingly, and the next batch of up to three elements are
* compared to the lastly updated top of the stack. This prevents integers -
* that are sent to the top of stack A and find themselves either already sorted
* or very close to being sorted - from being sent around the stacks,
* potentially several times, only to be sorted much later.
*
* Please note that other optimiztions can still be implemented to improve the
* current program even further.
*/
void	split_and_sort(t_stack *stack_a, t_stack *stack_b, t_map map)
{
	if (map.chunk_max.size > 3)
		split_and_sort(stack_a, stack_b, split_max(stack_a, stack_b, map));
	else if (map.chunk_max.size > 0)
		sort_chunk_max(stack_a, stack_b, &map);
	if (map.chunk_mid.size > 3)
		split_and_sort(stack_a, stack_b, split_mid(stack_a, stack_b, map));
	else if (map.chunk_mid.size > 0)
	{
		if (map.chunk_mid.position == TOP_B)
			merge_top_b(stack_a, stack_b, map.chunk_mid.size);
		else
			merge_bottom_a(stack_a, stack_b, map.chunk_mid.size);
	}
	if (map.chunk_min.size > 3)
		split_and_sort(stack_a, stack_b, split_min(stack_a, stack_b, map));
	else if (map.chunk_min.size > 0)
	{
		if (map.chunk_min.position == TOP_B)
			merge_top_b(stack_a, stack_b, map.chunk_min.size);
		else
			merge_bottom_b(stack_a, stack_b, map.chunk_min.size);
	}
}

static t_map	split_max(t_stack *stack_a, t_stack *stack_b, t_map map)
{
	size_t		initial_n;
	int32_t		low_pivot;
	int32_t		high_pivot;
	uint16_t	truncation_size;

	initial_n = init_split(&map, &map.chunk_max, &low_pivot,
			&high_pivot);
	truncation_size = 0;
	while (initial_n)
	{
		if (map.chunk_max.position == BOTTOM_A)
			reverse_rotate_stack(stack_a, stack_b, 'a');
		if (stack_a->array[stack_a->top] >= high_pivot)
			truncation_size += max_to_max(stack_a, stack_b, &map);
		else if (stack_a->array[stack_a->top] >= low_pivot)
			max_to_mid(stack_a, stack_b, &map.chunk_mid.size);
		else
			max_to_min(stack_a, stack_b, &map.chunk_min.size);
		initial_n--;
	}
	high_pivot += truncation_size;
	update_chunk_limits(&map, low_pivot, high_pivot);
	update_positions_max(&map, stack_a->n);
	return (map);
}

static void	sort_chunk_max(t_stack *stack_a, t_stack *stack_b, t_map *map)
{
	size_t	top;

	top = stack_a->top;
	if (map->chunk_max.size == stack_a->n)
	{
		if (map->chunk_max.size == 2)
		{
			if (stack_a->array[top] > stack_a->array[(top + 1) % stack_a->n])
				swap_top(stack_a, stack_b, 'a');
		}
		else if (map->chunk_max.size == 3)
			sort_three(stack_a, &stack_a->top, stack_a->n, stack_b);
	}
	else if (map->chunk_max.position == TOP_A)
		sort_top_a(stack_a, stack_b, map->chunk_max.size);
	else
	{
		merge_bottom_a(stack_a, stack_b, map->chunk_max.size);
		map->chunk_max.position = TOP_A;
	}
}

static t_map	split_mid(t_stack *stack_a, t_stack *stack_b, t_map map)
{
	if (map.chunk_mid.position == TOP_B)
		split_mid_from_top_b(&map, stack_a, stack_b);
	else
		split_mid_from_bottom_a(&map, stack_a, stack_b);
	update_positions_mid(&map);
	return (map);
}

static t_map	split_min(t_stack *stack_a, t_stack *stack_b, t_map map)
{
	size_t		initial_n;
	int32_t		low_pivot;
	int32_t		high_pivot;
	uint16_t	truncation_size;

	initial_n = init_split(&map, &map.chunk_min, &low_pivot, &high_pivot);
	truncation_size = 0;
	while (initial_n)
	{
		if (map.chunk_min.position == BOTTOM_B)
			reverse_rotate_stack(stack_a, stack_b, 'b');
		if (stack_b->array[stack_b->top] >= high_pivot)
			truncation_size += min_to_max(stack_a, stack_b,
					&map.chunk_max.size);
		else if (stack_b->array[stack_b->top] >= low_pivot)
			min_to_mid(stack_a, stack_b, &map.chunk_mid.size);
		else
			min_to_min(stack_a, stack_b, &map);
		initial_n--;
	}
	high_pivot += truncation_size;
	update_chunk_limits(&map, low_pivot, high_pivot);
	update_positions_min(&map, stack_b->n);
	return (map);
}
