/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:54:41 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/10 20:54:01 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_to_nbr(const char *nptr, size_t i);
static int	is_pos_or_neg(const char *nptr, size_t *i, int *sign);
static void	scan_isspace(const char *nptr, size_t *i);

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			return (digit_to_nbr(nptr, i) * sign);
		if (nptr[i] == '+' || nptr[i] == '-')
		{
			if (!is_pos_or_neg(nptr, &i, &sign))
				return (0);
		}
		else if (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
			scan_isspace(nptr, &i);
		else
			break ;
	}
	return (0);
}

static int	digit_to_nbr(const char *nptr, size_t i)
{
	int	result;

	while (nptr[i] == '0' && nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
		i++;
	result = (nptr[i] - '0');
	while (nptr[i + 1] >= '0' && nptr[i + 1] <= '9')
	{
		i++;
		result = result * 10 + (nptr[i] - '0');
	}
	return (result);
}

static int	is_pos_or_neg(const char *nptr, size_t *i, int *sign)
{
	if (nptr[*i + 1] >= '0' && nptr[*i + 1] <= '9')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
		return (1);
	}
	else
		return (0);
}

static void	scan_isspace(const char *nptr, size_t *i)
{
	while (nptr[*i] == 32 || (nptr[*i] >= 9 && nptr[*i] <= 13))
		(*i)++;
}
