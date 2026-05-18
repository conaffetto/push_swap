/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_min_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:19:39 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/26 16:19:51 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

uint8_t	min_to_max(t_stack *stack_a, t_stack *stack_b, size_t *size)
{
	push(stack_b, stack_a, 'a');
	(*size)++;
	if (*size < 4)
		return (early_sort(stack_a, size, stack_b));
	return (0);
}

void	min_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size)
{
	push(stack_b, stack_a, 'a');
	rotate_stack(stack_a, stack_b, 'a');
	(*size)++;
}

void	min_to_min(t_stack *stack_a, t_stack *stack_b, t_map *map)
{
	if (map->chunk_min.position == TOP_B)
		rotate_stack(stack_a, stack_b, 'b');
	map->chunk_min.size++;
}

void	update_positions_min(t_map *map, size_t stack_b_n)
{
	map->chunk_max.position = TOP_A;
	map->chunk_mid.position = BOTTOM_A;
	if (map->chunk_min.position == TOP_B
		&& map->chunk_min.size != stack_b_n)
		map->chunk_min.position = BOTTOM_B;
	else
		map->chunk_min.position = TOP_B;
}
