/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:21:47 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/15 17:29:00 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	substr = NULL;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *) ft_calloc(1, sizeof (char));
		return (substr);
	}
	if (len <= ft_strlen(s) - start)
	{
		substr = (char *) ft_calloc(len + 1, sizeof (char));
		if (substr == NULL)
			return (NULL);
	}
	else
	{
		substr = (char *) ft_calloc(ft_strlen(s) - start + 1, sizeof (char));
		if (substr == NULL)
			return (NULL);
		len = ft_strlen(s) - start;
	}
	substr = (char *)ft_memcpy(substr, &s[start], len);
	return (substr);
}
