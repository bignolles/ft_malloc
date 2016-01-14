/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_sizestr(const char *str)
{
	size_t	size;

	size = 0;
	while (str[size] != '\00')
	{
		size++;
	}
	return (size);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*p1;
	char	*p2;
	char	*p1begin;

	p1 = (char *)s1;
	if (ft_sizestr(s1) < ft_sizestr(s2))
		return (NULL);
	if (ft_sizestr(s1) == 0 || ft_sizestr(s2) == 0)
		return (p1);
	while (*p1)
	{
		p1begin = p1;
		p2 = (char *)s2;
		while (*p1 && *p2 && *p1 == *p2)
		{
			p1++;
			p2++;
		}
		if (!*p2)
			return (p1begin);
		p1 = p1begin + 1;
	}
	return (NULL);
}
