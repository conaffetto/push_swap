/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:41:08 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/20 19:06:53 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_entire_s1(char const *s1);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_result;
	size_t	i;
	int		j;

	trimmed_result = NULL;
	if (s1 == NULL)
		return (NULL);
	if (!set || !*set)
	{
		trimmed_result = copy_entire_s1(s1);
		return (trimmed_result);
	}
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= (int )i && ft_strchr(set, s1[j]))
		j--;
	trimmed_result = (char *) ft_calloc((j - i + 2), sizeof (char));
	if (trimmed_result == NULL)
		return (NULL);
	trimmed_result = (char *) ft_memcpy(trimmed_result, s1 + i, (j - i + 1));
	return (trimmed_result);
}

static char	*copy_entire_s1(char const *s1)
{
	char	*dest;

	dest = NULL;
	dest = (char *) ft_calloc((ft_strlen(s1) + 1), sizeof (char));
	if (!dest)
		return (NULL);
	dest = (char *) ft_memcpy(dest, s1, ft_strlen(s1));
	return (dest);
}
