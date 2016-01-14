/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:11 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:11 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	int		i;

	p = (char *)s;
	i = 0;
	while (s[i] != '\00')
	{
		if (s[i] == (char)c)
			return (p + i);
		i++;
	}
	if (c == '\00')
		return (p + i);
	return (NULL);
}
