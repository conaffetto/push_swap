/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:43:49 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/17 19:07:18 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*int_min_special_treatment(char *str);
static size_t	isnegative(int *n);
static char		*conv_to_s(int n, size_t sign, size_t n_digits, long long x);

char	*ft_itoa(int n)
{
	size_t		n_digits;
	size_t		sign;
	long long	x;
	char		*str;

	str = NULL;
	if (n == -2147483648)
		return (int_min_special_treatment(str));
	sign = isnegative(&n);
	x = 1;
	n_digits = 1;
	while (n / x / 10 >= 1 && n != 0)
	{
		x *= 10;
		n_digits++;
	}
	str = conv_to_s(n, sign, n_digits, x);
	return (str);
}

static char	*int_min_special_treatment(char *str)
{
	str = (char *) ft_calloc(12, sizeof (char));
	if (!str)
		return (NULL);
	str = (char *) ft_memcpy(str, "-2147483648", 12);
	return (str);
}

static size_t	isnegative(int *n)
{
	size_t	sign;

	if (*n >= 0)
		sign = 0;
	else
	{
		sign = 1;
		*n = -(*n);
	}
	return (sign);
}

static char	*conv_to_s(int n, size_t sign, size_t n_digits, long long x)
{
	char	*s;
	size_t	i;

	s = (char *) ft_calloc((sign + n_digits + 1), sizeof (char));
	if (!s)
		return (NULL);
	i = 0;
	if (sign == 1)
	{
		s[i] = '-';
		i++;
	}
	while (n_digits > 0)
	{
		s[i] = n % (x * 10) / x + '0';
		x /= 10;
		n_digits--;
		i++;
	}
	return (s);
}
