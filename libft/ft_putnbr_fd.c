/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:28:40 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/18 20:51:54 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_all_digits(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	write_all_digits(n, fd);
}

static void	write_all_digits(int n, int fd)
{
	size_t		n_of_digits;
	long long	x;
	char		digit;

	n_of_digits = 1;
	x = 10;
	while (n / x >= 1)
	{
		n_of_digits += 1;
		x *= 10;
	}
	x /= 10;
	while (n_of_digits > 0)
	{
		digit = n / x % 10 + '0';
		write(fd, &digit, 1);
		x /= 10;
		n_of_digits--;
	}
}
