/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:18:35 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/03 21:42:39 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*pointer;
	size_t	i;

	pointer = NULL;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			pointer = ((char *) &s[i]);
			return (pointer);
		}
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
	{
		pointer = ((char *) &s[i]);
		return (pointer);
	}
	return (NULL);
}
