/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:37:01 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/06 23:43:21 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_c(const char *s, const char c, size_t i, char **p);
static size_t	sncmp(const char *s1, const char *s2, size_t *n, size_t *i);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*pointer;
	char	**deref_agent;

	i = 0;
	pointer = NULL;
	deref_agent = &pointer;
	if ((!big || !little) && len == 0)
		return (NULL);
	while (little[0])
	{
		while (big[i] && i < len && pointer == NULL)
			i = find_c(big, little[0], i, deref_agent);
		if (pointer == NULL)
			return (NULL);
		j = sncmp(big, little, &len, &i);
		if (!little[j])
			return (pointer);
		if (!big[i] || i == len)
			return (NULL);
		pointer = NULL;
	}
	return ((char *)big);
}

static size_t	find_c(const char *s, const char c, size_t i, char **p)
{
	if (s[i] == c)
		*p = ((char *)&s[i]);
	else
		i++;
	return (i);
}

static size_t	sncmp(const char *s1, const char *s2, size_t *n, size_t *i)
{
	size_t	j;

	j = 0;
	while (s1[*i] == s2[j] && *i < *n && s2[j])
	{
		(*i)++;
		j++;
	}
	if (s1[*i] != s2[j])
		(*i) = *i - j + 1;
	return (j);
}
