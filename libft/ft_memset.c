/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:09 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:09 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		*((char *)b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}
