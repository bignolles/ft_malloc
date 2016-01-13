/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 13:37:18 by ndatin            #+#    #+#             */
/*   Updated: 2016/01/13 13:48:02 by ndatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_malloc.h>

int	init_tiny_small(void *tiny, void *small)
{
	int	size;
	int	pagesize;

	pagesize = getpagesize();
	size = TINY_PAGES_NB * pagesize;
	tiny = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (tiny == MAP_FAILED)
		return (0);
	ft_bzero(tiny, size);
	size = SMALL_PAGES_NB * pagesize;
	small = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (small == MAP_FAILED)
		return (0);
	ft_bzero(small, size);
	return (1);
}
