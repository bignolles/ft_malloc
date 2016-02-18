/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 13:37:18 by ndatin            #+#    #+#             */
/*   Updated: 2016/02/18 17:35:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static int	init_tiny(void)
{
	int		size;
	int		pagesize;

	pagesize = getpagesize();
	size = TINY_PAGES_NB * pagesize;
	g_malloc_data.data_tiny = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (g_malloc_data.data_tiny == MAP_FAILED)
		return (M_NOK);
	ft_bzero(g_malloc_data.data_tiny, size);
	g_malloc_data.datas_len[TINY] = size;
	g_malloc_data.datas[TINY] = g_malloc_data.data_tiny;
	g_malloc_data.datas_end[TINY] = g_malloc_data.data_tiny + size;
	g_malloc_data.max_size[TINY] = defragment_memory(TINY);
	return (M_OK);
}

static int	init_small(void)
{
	int		size;
	int		pagesize;

	pagesize = getpagesize();
	size = SMALL_PAGES_NB * pagesize;
	g_malloc_data.data_small = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (g_malloc_data.data_small == MAP_FAILED)
		return (M_NOK);
	ft_bzero(g_malloc_data.data_small, size);
	*(int32_t*)g_malloc_data.data_small = -1 * size;
	g_malloc_data.datas_len[SMALL] = size;
	g_malloc_data.datas[SMALL] = g_malloc_data.data_small;
	g_malloc_data.datas_end[SMALL] = g_malloc_data.data_small + size;
	g_malloc_data.max_size[SMALL] = defragment_memory(SMALL);
	return (M_OK);
}

int			pages_init(t_blocksize blk_size)
{
	int		size;
	int		pagesize;

	pagesize = getpagesize();
	if (blk_size == TINY)
		return (init_tiny());
	if (blk_size == SMALL)
		return (init_small());
	if (blk_size == LARGE)
	{
		size = LARGE_PAGES_NB * pagesize;
		g_malloc_data.meta_large = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
		g_malloc_data.meta_large_len = size / sizeof(void*);
		if (g_malloc_data.meta_large == MAP_FAILED)
			return (M_NOK);
		ft_bzero(g_malloc_data.meta_large, size);
	}
	return (M_OK);
}
