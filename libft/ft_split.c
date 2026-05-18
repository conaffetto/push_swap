/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:09:14 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/21 21:04:44 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_number_of_strings(char const *s, char c);
static char		**split_process(char **result, char *scanner, char c,
					size_t n_of_strings);
static char		*find_next_string(char *scanner, char c, size_t *length);
static void		free_all(char **result, size_t j);

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*scanner;
	size_t	n_of_strings;

	result = NULL;
	scanner = NULL;
	if (!s)
		return (NULL);
	if (!*s)
	{
		result = (char **) ft_calloc(1, sizeof (char *));
		if (!result)
			return (NULL);
		*result = NULL;
		return (result);
	}
	n_of_strings = count_number_of_strings(s, c);
	result = (char **) ft_calloc(n_of_strings + 1, sizeof (char *));
	if (!result)
		return (NULL);
	scanner = (char *)s;
	result = split_process(result, scanner, c, n_of_strings);
	if (!result)
		return (NULL);
	return (result);
}

static size_t	count_number_of_strings(char const *s, char c)
{
	size_t	n_of_strings;
	char	*scanner;

	scanner = NULL;
	scanner = (char *) s;
	n_of_strings = 0;
	while (*scanner)
	{
		if (*scanner != c)
		{
			n_of_strings++;
			while (*scanner && *scanner != c)
				scanner++;
		}
		if (*scanner == c && c != '\0')
		{
			while (*scanner == c)
				scanner++;
		}
	}
	return (n_of_strings);
}

static char	**split_process(char **result, char *scanner, char c,
				size_t n_of_strings)
{
	size_t	j;
	size_t	length;

	j = 0;
	while (j < n_of_strings)
	{
		length = 0;
		scanner = find_next_string(scanner, c, &length);
		result[j] = ft_substr(scanner, 0, length);
		if (!result[j])
		{
			free_all(result, j);
			return (NULL);
		}
		j++;
		scanner += length;
	}
	return (result);
}

static char	*find_next_string(char *scanner, char c, size_t *length)
{
	while (*scanner && *scanner == c)
	{
		scanner++;
		(*length)++;
	}
	if (!*scanner)
		return (scanner);
	else
	{
		*length = 0;
		while (*scanner && *scanner != c)
		{
			scanner++;
			(*length)++;
		}
	}
	return (scanner - (*length));
}

static void	free_all(char **result, size_t j)
{
	j = 0;
	while (result[j])
	{
		free (result[j]);
		result[j] = NULL;
		j++;
	}
	free (result);
	result = NULL;
}
