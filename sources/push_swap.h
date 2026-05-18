/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:23:12 by ykadosh           #+#    #+#             */
/*   Updated: 2025/02/27 14:44:03 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

// system / standard libraries
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

// static library
# include "../libft/libft.h"

typedef struct s_stack
{
	int		*array;
	size_t	n;
	size_t	top;
}	t_stack;

typedef struct s_chunk
{
	uint8_t	position;
	size_t	size;
	int		min_v;
	int		max_v;
}	t_chunk;

typedef struct s_map
{
	t_chunk	chunk_max;
	t_chunk	chunk_mid;
	t_chunk	chunk_min;
}	t_map;

typedef enum e_position
{
	TOP_A,
	BOTTOM_A,
	TOP_B,
	BOTTOM_B
}	t_position;

// parsing prototypes
size_t	count_total_argv_numbers(int argc, char **argv);
int		ft_isspace(int c);
int		ft_issign(int c);
void	ft_numeric_strchr(char **str);
uint8_t	parse_argv(char **argv, int argc, t_stack *stack_a);
int64_t	custom_atoi(char **str);

// indexing through double pivot quick sort
uint8_t	assign_indices(int *array_a, int *array_b, size_t n);
uint8_t	double_pivot_quick_sort(int *array, size_t n);

// memory control
uint8_t	allocate_array(int **array, size_t size);
void	free_single_stack(int **array);
void	free_both_stacks(int **array_a, int **array_b);

// utilities
void	invalid_input_found(void);
void	ft_swap(int *x, int *y);
uint8_t	is_sorted_circular_array(int *array, size_t n, size_t top);

// push_swap instructions
void	swap_top(t_stack *stack_a, t_stack *stack_b, char id);
void	rotate_stack(t_stack *stack_a, t_stack *stack_b, char id);
void	reverse_rotate_stack(t_stack *stack_a, t_stack *stack_b, char id);
void	push(t_stack *origin, t_stack *target, char id);
void	swap_rotate(t_stack *stack_a, t_stack *stack_b, uint8_t scenario);

// sorting functions
void	handle_one_or_two_integers(t_stack *stack_a);
void	sort_three(t_stack *stack_a, size_t *top, size_t n, t_stack *stack_b);
void	merge_top_b(t_stack *stack_a, t_stack *stack_b, size_t size);
void	merge_bottom_a(t_stack *stack_a, t_stack *stack_b, size_t size);
void	merge_bottom_b(t_stack *stack_a, t_stack *stack_b, size_t size);
void	sort_top_a(t_stack *stack_a, t_stack *stack_b, size_t size);

// split_and_sort() prototypes
void	split_and_sort(t_stack *stack_a, t_stack *stack_b, t_map map);
size_t	init_split(t_map *map, t_chunk *chunk_to_split, int32_t *low_pivot,
			int32_t *high_pivot);
uint8_t	early_sort(t_stack *stack_a, size_t *size, t_stack *stack_b);
void	update_chunk_limits(t_map *map, int32_t low_pivot, int32_t high_pivot);

// split_max() utilities
uint8_t	max_to_max(t_stack *stack_a, t_stack *stack_b, t_map *map);
void	max_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size);
void	max_to_min(t_stack *stack_a, t_stack *stack_b, size_t *size);
void	update_positions_max(t_map *map, size_t stack_a_n);

// split_mid() utilities
void	split_mid_from_top_b(t_map *map, t_stack *stack_a, t_stack *stack_b);
void	split_mid_from_bottom_a(t_map *map, t_stack *stack_a, t_stack *stack_b);
void	update_positions_mid(t_map *map);

// split_min() utilities
uint8_t	min_to_max(t_stack *stack_a, t_stack *stack_b, size_t *size);
void	min_to_mid(t_stack *stack_a, t_stack *stack_b, size_t *size);
void	min_to_min(t_stack *stack_a, t_stack *stack_b, t_map *map);
void	update_positions_min(t_map *map, size_t stack_b_n);

#endif
