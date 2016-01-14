/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:12 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:12 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;

	size_dst = 0;
	size_src = 0;
	i = 0;
	while (dst[size_dst] != '\00')
	{
		size_dst++;
	}
	while (src[size_src] != '\00')
	{
		size_src++;
	}
	if (size < size_dst)
		return (size + size_src);
	while ((size_dst + i + 1) < size)
	{
		dst[size_dst + i] = src[i];
		i++;
	}
	dst[size_dst + i] = '\00';
	return (size_dst + size_src);
}
