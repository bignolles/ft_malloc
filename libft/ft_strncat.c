/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:12 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:12 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = dest;
	while (dest[i] != '\00')
	{
		i++;
	}
	while (src[j] != '\00' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\00';
	return (res);
}
