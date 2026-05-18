/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 22:50:15 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/26 23:07:26 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	designate_pivots(t_chunk *chunk_to_split, int32_t *low_pivot,
				int32_t *high_pivot);

size_t	init_split(t_map *map, t_chunk *chunk_to_split, int32_t *low_pivot,
			int32_t *high_pivot)
{
	size_t	initial_n;

	designate_pivots(chunk_to_split, low_pivot, high_pivot);
	initial_n = chunk_to_split->size;
	map->chunk_max.size = 0;
	map->chunk_mid.size = 0;
	map->chunk_min.size = 0;
	return (initial_n);
}

/*
* The algorithm implemented in this program's recursive splitting of the stacks
* uses two pivots, chosen between the range of the chunk's values. This program
* attempts to split each chunk to three subchunks which are roughly equal in
* size. This is made possible thanks to the indexing that is brought to the
* stack's integers prior to the splitting process, ensuring that each chunk
* will have every single value between its smallest value ("min_v") and its
* largest value ("max_v").
* If, however, there are less than nine integers within a chunk, low_pivot is
* set to the chunk's smallest value, and high_pivot is set to (roughly) the
* range's middle value, in order to split the chunk into two subchunks instead
* of three. This is done in order to mitigate the quantity of push_swap
* instructions, because sending values to chunk MIN, often located at position
* BOTTOM B, involves extra rotations and reverse rotations, which are not very
* beneficial when the chunk is rather small.
*/
static void	designate_pivots(t_chunk *chunk_to_split, int32_t *low_pivot,
				int32_t *high_pivot)
{
	if (chunk_to_split->size >= 9)
	{
		*low_pivot = chunk_to_split->min_v + chunk_to_split->size * .34;
		*high_pivot = chunk_to_split->min_v + chunk_to_split->size * .67;
	}
	else
	{
		*low_pivot = chunk_to_split->min_v;
		*high_pivot = chunk_to_split->min_v + chunk_to_split->size * .40;
	}
}

/*
* Before returning the map containing the chunks' properties, the program has
* to make sure that the next chunk splitting function call receives the correct
* boundaries of each chunk; Otherwise, the pivots will not be calculated
* properly, and the sorting process will be thrown off balance.
*/
void	update_chunk_limits(t_map *map, int32_t low_pivot, int32_t high_pivot)
{
	map->chunk_max.min_v = high_pivot;
	map->chunk_max.max_v = high_pivot + map->chunk_max.size - 1;
	map->chunk_mid.min_v = low_pivot;
	map->chunk_mid.max_v = high_pivot - 1;
	map->chunk_min.min_v = low_pivot - map->chunk_min.size;
	map->chunk_min.max_v = low_pivot - 1;
}

void	update_positions_mid(t_map *map)
{
	map->chunk_max.position = TOP_A;
	map->chunk_min.position = BOTTOM_B;
	if (map->chunk_mid.position == TOP_B)
		map->chunk_mid.position = BOTTOM_A;
	else
		map->chunk_mid.position = TOP_B;
}
