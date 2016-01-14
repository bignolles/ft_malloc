/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_getlen(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\00')
		size++;
	return (size);
}

static int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n == 1 && *s1 == *s2)
		return (0);
	while (s1[i] != '\00' && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	if (s1[i] < s2[i])
		return (1);
	else if (s1[i] > s2[i])
		return (-1);
	else
		return (0);
	return (s1[i] - s2[i]);
}

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	c;
	char	sc;
	size_t	len;
	char	b1;

	b1 = 0;
	if ((c = *s2++) != '\0')
	{
		len = ft_getlen(s2);
		while (ft_strncmp(s1, s2, len) != 0 || !b1)
		{
			b1 = 0;
			while (sc != c || !b1)
			{
				b1 = 1;
				if ((sc = *s1++) == '\0' || n-- < 1)
					return (NULL);
			}
			if (len > n)
				return (NULL);
		}
		s1--;
	}
	return ((char *)s1);
}
