/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:09 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:09 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	void			*old_s1;

	if (!s1 || !s2)
		return (NULL);
	old_s1 = s1;
	i = 0;
	while (i < n)
	{
		*((char *)s1 + i) = *((char *)s2 + i);
		i++;
	}
	return (old_s1);
}
