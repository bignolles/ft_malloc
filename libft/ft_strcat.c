/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:11 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:11 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;
	char	*orig;

	orig = dest;
	i = 0;
	while (dest[i] != '\00')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\00')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\00';
	return (orig);
}
