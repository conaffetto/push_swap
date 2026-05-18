/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:52:05 by ykadosh           #+#    #+#             */
/*   Updated: 2025/03/12 22:13:21 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	count_nbrs_in_single_str(char *s);
static void		parse_single_string(char *string, t_stack *stack_a);

/*
* This function processes the entirety of the command-line arguments passed
* to the push_swap program, and returns the total quantity of numbers found.
* If an invalid input is encountered during the process, the program quits
* with exit status 2.
* NOTE: The count can include numbers which are outside the range of int, and
* also duplicates of the same number. Those invalid inputs are only detected
* later on in the program. At the end of the function's execution, if the count
* result is 0, it means that argv contains solely empty and/or whitespace
* strings: this is then handled as an invalid input, and exits.
*/
size_t	count_total_argv_numbers(int argc, char **argv)
{
	size_t	n;
	int		i;

	n = 0;
	i = 1;
	while (i < argc)
	{
		n += (count_nbrs_in_single_str(argv[i]));
		i++;
	}
	if (!n)
		invalid_input_found();
	return (n);
}

/*
* counts and returns the number of valid numbers found within a single string.
* if an invalid input is found, the program quits with exit status 2.
* takes whitespace into account.
* NOTE: n_numbers may contain integers outside of int's range, at the end of
* the function's execution. Those are handled later on, in the custom_atoi()
*/
static size_t	count_nbrs_in_single_str(char *s)
{
	size_t	n_numbers;

	n_numbers = 0;
	while (*s)
	{
		if (!ft_isdigit(*s) && !ft_issign(*s) && !ft_isspace(*s))
			invalid_input_found();
		if (ft_isdigit(*s) || ft_issign(*s))
		{
			if (ft_issign(*s))
			{
				s++;
				if (!ft_isdigit(*s))
					invalid_input_found();
			}
			while (ft_isdigit(*s))
				s++;
			if (*s && !ft_isspace(*s))
				invalid_input_found();
			n_numbers++;
		}
		while (ft_isspace(*s))
			s++;
	}
	return (n_numbers);
}

/*
* parses through all of argv's arguments, and stores all valid integers into
* the stack, in order of appearance. If an invalid input is found during
* the parsing process (empty string, whitespace string, or integer overflow),
* the program terminates and an error message is displayed.
* If, at the end of this function, there is only one or two integers in the
* stack, those are handled by calling handle_one_or_two_integers().
*
* NOTE: At the end of this function, the stack might contain duplicates. Those
* are only detected later on in the program, in assign_indices() and its helper
* functions.
*/
uint8_t	parse_argv(char **argv, int argc, t_stack *stack_a)
{
	int	j;

	stack_a->n = 0;
	j = 1;
	while (j < argc)
	{
		parse_single_string(argv[j], stack_a);
		j++;
	}
	if (stack_a->n == 1 || stack_a->n == 2)
	{
		handle_one_or_two_integers(stack_a);
		return (0);
	}
	return (1);
}

/*
* converts all valid integers found within a single string.
* If a string is found to be empty (whether it is a null string or a
* whitespace string), it is considered to be an invalid input and an error
* message is displayed. Likewise, this function checks for integer overflows
* and similarly handles that invalid input
*/
static void	parse_single_string(char *string, t_stack *stack_a)
{
	int64_t	nbr;
	size_t	temp;

	nbr = 0;
	temp = stack_a->n;
	while (*string)
	{
		ft_numeric_strchr(&string);
		if (*string)
		{
			nbr = custom_atoi(&string);
			if (nbr > INT_MAX || nbr < INT_MIN)
			{
				free_single_stack(&stack_a->array);
				invalid_input_found();
			}
			stack_a->array[stack_a->n] = (int) nbr;
			stack_a->n++;
		}
	}
	if (temp == stack_a->n)
	{
		free_single_stack(&stack_a->array);
		invalid_input_found();
	}
}

/*
* At this point, while the numbers within argv are always valid ones (meaning
* that they do not contain characters other than decimal digits and, at most,
* a single positive or negative sign preceding those digits), they might:
*	1. not be within the range of int;
*	2. be 'nonexistent' - meaning that the argument/s may still contain at
*	least one EMPTY string and/or whitespace string; these are cases of
*	invalid input, and should be treated as such.
*	3. contain duplicates
* NOTE: parse_single_string() handles the first two of the above conditions,
* with the help of custom_atoi(). However:
*	1. Duplicated integers should still be checked for later in the program.
*	2. the return value of custom_atoi() is int64_t (a.k.a 'long' on 64 bit
*	architectures), so that the caller can check for the overflow, and if none
*	is found, it can then safely cast that returned value into an int when
*	assigning it to the stack.
*/
int64_t	custom_atoi(char **str)
{
	int64_t	nbr;
	int64_t	conversion;
	int8_t	sign;

	nbr = 0;
	sign = 1;
	if (ft_issign(**str))
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (ft_isdigit(**str))
	{
		nbr = nbr * 10 + (**str - '0');
		conversion = nbr * sign;
		if (conversion > INT_MAX || conversion < INT_MIN)
			return (conversion);
		(*str)++;
	}
	return (conversion);
}
