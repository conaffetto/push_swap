/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:55:45 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/08 15:44:37 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	initial_dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (src_len + size);
	initial_dst_len = ft_strlen(dst);
	if (size <= initial_dst_len)
		return (src_len + size);
	dst += initial_dst_len;
	i = 0;
	while (src[i] && i < (size - initial_dst_len - 1))
	{
		*dst = src[i];
		i++;
		dst++;
	}
	*dst = '\0';
	return (initial_dst_len + src_len);
}
