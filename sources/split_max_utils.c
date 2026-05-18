/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_max_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:38:18 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/26 16:03:25 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

uint8_t	max_to_max(t_stack *stack_a, t_stack *stack_b, t_map *map)
{
	if (map->chunk_max.position == TOP_A)
		rotate_stack(stack_a, stack_b, 'a');
	map->chunk_max.size++;
	if (map->chunk_max.position == BOTTOM_A && map->chunk_max.size < 4)
		return (early_sort(stack_a, &map->chunk_max.size, stack_b));
	return (0);
}

void	max_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size)
{
	push(stack_a, stack_b, 'b');
	(*size)++;
}

void	max_to_min(t_stack *stack_a, t_stack *stack_b, size_t *size)
{
	push(stack_a, stack_b, 'b');
	rotate_stack(stack_a, stack_b, 'b');
	(*size)++;
}

/*
* the POSITION of MAX has to be updated only:
* - when splitting the other chunks (i.e. MID or MIN), the MAX values are
*   always sent to TOP A
* - when we split MAX and it is located at position TOP A: if there are other
*   chunks below it in the same stack, the 'decoy' effect is gone and the
*   position of chunk MAX has to be updated to BOTTOM A, because its max values
*   are sent to the bottom of the stack and the newly created chunk MAX
*   will not be the only chunk present in that stack.
* - when its position is BOTTOM A, the next position will always be TOP A.
* - when we merge and sort elements from a chunk into TOP A instead of
*   splitting it
*/
void	update_positions_max(t_map *map, size_t stack_a_n)
{
	map->chunk_mid.position = TOP_B;
	map->chunk_min.position = BOTTOM_B;
	if (map->chunk_max.position == TOP_A && map->chunk_max.size != stack_a_n)
		map->chunk_max.position = BOTTOM_A;
	else if (map->chunk_max.position == BOTTOM_A)
		map->chunk_max.position = TOP_A;
}
