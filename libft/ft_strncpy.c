/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;
	size_t	size_src;

	i = 0;
	size_src = 0;
	while (src[size_src] != '\00')
		size_src++;
	while (i < n)
	{
		if (!size_src)
			dest[i] = '\00';
		else
			dest[i] = src[i];
		i++;
	}
	if (n > size_src)
	{
		while (n > size_src)
		{
			dest[i] = '\00';
			i++;
			n--;
		}
	}
	return (dest);
}
