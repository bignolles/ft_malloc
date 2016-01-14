/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:09 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:09 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void			*buf;
	unsigned int	i;

	if (size > 0)
	{
		i = 0;
		buf = (void *)malloc(sizeof(buf) * size);
		if (!buf)
			return (NULL);
		while (i < size)
		{
			*((char *)buf + i) = '\00';
			i++;
		}
		return (buf);
	}
	return (NULL);
}
