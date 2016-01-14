/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:11 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:11 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_realloc(void *mem, size_t new_size)
{
	void	*new_mem;
	size_t	old_size;

	if (!mem)
		return (NULL);
	old_size = ft_strlen((char *)mem);
	if (old_size == 0)
		return (mem);
	new_mem = ft_memalloc(new_size);
	if (!new_mem)
		return (NULL);
	ft_memcpy(new_mem, mem, old_size);
	free(mem);
	return (new_mem);
}
