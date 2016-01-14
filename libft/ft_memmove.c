/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:09 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:09 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = (void *)malloc(sizeof(char) * n);
	if (!tmp)
		return (NULL);
	while (i < n)
	{
		*((char *)tmp + i) = *((char *)src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*((char *)dest + i) = *((char *)tmp + i);
		i++;
	}
	free(tmp);
	return (dest);
}
