/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:49:51 by ykadosh           #+#    #+#             */
/*   Updated: 2025/02/27 14:03:47 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
* returns true if the character passed as an argument is a space (' '),
* horizontal tab ('\t'), newline ('\n'), vertical tab ('\v'),
* form-feed ('\f'), or carriage return ('\r'),
*/
int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/*
* returns true if the character passed as an argument is a '+' or '-' sign
*/
int	ft_issign(int c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

/*
* advances the string (passed as a double pointer argument) to the first
* location of either a positive/negative sign or a digit.
* if none were found, the pointer will point at the string's nul terminator
* at the end of the function's execution, since it is a double pointer
*/
void	ft_numeric_strchr(char **str)
{
	while (**str && !ft_issign(**str) && !ft_isdigit(**str))
		(*str)++;
}
