/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occ;

	occ = NULL;
	i = 0;
	while (s[i] != '\00')
	{
		if (s[i] == (char)c)
			occ = (char *)s + i;
		i++;
	}
	if (c == '\00')
		return ((char *)s + i);
	return (occ);
}
