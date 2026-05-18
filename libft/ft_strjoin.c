/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadosh <ykadosh@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:33:17 by ykadosh           #+#    #+#             */
/*   Updated: 2024/11/15 18:50:35 by ykadosh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;

	cat = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	cat = (char *) malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (cat == NULL)
		return (NULL);
	cat = (char *) ft_memcpy(cat, s1, (ft_strlen(s1)));
	cat = cat + ft_strlen(s1);
	cat = (char *) ft_memcpy(cat, s2, (ft_strlen(s2) + 1));
	cat = cat - ft_strlen(s1);
	return (cat);
}
