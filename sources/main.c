/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:46:10 by ykadosh           #+#    #+#             */
/*   Updated: 2025/02/27 14:43:57 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_stacks(t_stack *stack_a, t_stack *stack_b);
static void	split_push_swap(t_stack *stack_a, t_stack *stack_b, t_map *map);
static void	init_chunk_map(t_map *map, size_t n);
static void	first_split(t_stack *stack_a, t_stack *stack_b, t_map *map);

/*
* exit status 1:	malloc() failure
* exit status 2:	invalid input found
* exit status 3:	write() failure
*/
int	main(int argc, char **argv)
{
	t_stack		stack_a;
	t_stack		stack_b;
	t_map		map;

	init_stacks(&stack_a, &stack_b);
	if (argc > 1)
	{
		stack_a.n = count_total_argv_numbers(argc, argv);
		if (!allocate_array(&stack_a.array, stack_a.n))
			return (1);
		if (!parse_argv(argv, argc, &stack_a))
			return (0);
		if (!allocate_array(&stack_b.array, stack_a.n))
		{
			free_single_stack(&stack_a.array);
			return (1);
		}
		if (assign_indices(stack_a.array, stack_b.array, stack_a.n))
			return (0);
		split_push_swap(&stack_a, &stack_b, &map);
		free_both_stacks(&stack_a.array, &stack_b.array);
	}
	return (0);
}

/*
* initialises all of the structs' values to 0 (or NULL)
*/
static void	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->array = NULL;
	stack_b->array = NULL;
	stack_a->n = 0;
	stack_b->n = 0;
	stack_a->top = 0;
	stack_b->top = 0;
}

static void	split_push_swap(t_stack *stack_a, t_stack *stack_b, t_map *map)
{
	init_chunk_map(map, stack_a->n);
	if (stack_a->n > 3)
		first_split(stack_a, stack_b, map);
	split_and_sort(stack_a, stack_b, *map);
}

/*
* init_chunk_map() basically initializes all chunk properties to zero - with
* a few exceptions:
* - Since it is only called from the very first split of the stack, we know
*   in which positions each subchunk (i.e. chunk_max, chunk_mid, and chunk_min)
*   will end up afterwards, therefore this function sets those chunks'
*   positions in advance.
* - chunk_max's minimum and maximum values are set to 0 and to (n - 1),
*   respectively, even though no split has been executed at this point of the
*   code, and therefore no 'true' chunk MAX has been created as of yet. For the
*   sake of simplicity, we can consider stack A as being chunk MAX, since it is
*   located in position TOP A (which is anyways the most natural position for
*   chunk MAX).
*/
static void	init_chunk_map(t_map *map, size_t n)
{
	map->chunk_max.position = TOP_A;
	map->chunk_max.size = n;
	map->chunk_max.min_v = 0;
	map->chunk_max.max_v = n - 1;
	map->chunk_mid.position = TOP_B;
	map->chunk_mid.size = 0;
	map->chunk_mid.min_v = 0;
	map->chunk_mid.max_v = 0;
	map->chunk_min.position = BOTTOM_B;
	map->chunk_min.size = 0;
	map->chunk_min.min_v = 0;
	map->chunk_min.max_v = 0;
}

/*
* The very first split of the stack into three subchunks: chunk MAX, chunk MID,
* and chunk MIN. Please refer to split_to_chunks.c for further information.
* Note that unlike the similar functions split_max(), split_mid() & split_min()
* we do not need to update the chunks' positions here, because those are being
* set in advance, within init_chunk_map(), called just before first_split().
*/
static void	first_split(t_stack *stack_a, t_stack *stack_b, t_map *map)
{
	size_t	initial_n;
	int32_t	low_pivot;
	int32_t	high_pivot;

	initial_n = init_split(map, &map->chunk_max, &low_pivot, &high_pivot);
	while (initial_n)
	{
		if (stack_a->array[stack_a->top] >= high_pivot)
			max_to_max(stack_a, stack_b, map);
		else if (stack_a->array[stack_a->top] >= low_pivot)
			max_to_mid(stack_a, stack_b, &map->chunk_mid.size);
		else
			max_to_min(stack_a, stack_b, &map->chunk_min.size);
		initial_n--;
	}
	update_chunk_limits(map, low_pivot, high_pivot);
}
