/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:37:08 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/03 21:57:42 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pointer;
	size_t	i;

	pointer = NULL;
	i = (ft_strlen(s));
	while (i > 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			pointer = ((char *) &s[i]);
			return (pointer);
		}
		i--;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
	{
		pointer = ((char *) &s[i]);
		return (pointer);
	}
	return (NULL);
}
