/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 13:37:18 by ndatin            #+#    #+#             */
/*   Updated: 2016/01/20 16:24:19 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;

static int	data_init()
{
	int	size;
	int	pagesize;

	pagesize = getpagesize();
	size = TINY_PAGES_NB * pagesize;
	malloc_data_g.data_tiny = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (malloc_data_g.data_tiny == MAP_FAILED)
	{
		ft_putendl("data_tiny init failed\n");
		return (M_NOK);
	}
	malloc_data_g.datas[TINY] = malloc_data_g.data_tiny;
	malloc_data_g.datas_end[TINY] = malloc_data_g.data_tiny + size;
	ft_bzero(malloc_data_g.data_tiny, size);
	size = SMALL_PAGES_NB * pagesize;
	malloc_data_g.data_small = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (malloc_data_g.data_small == MAP_FAILED)
	{
		ft_putendl("data_small init failed\n");
		return (M_NOK);
	}
	ft_bzero(malloc_data_g.data_small, size);
	malloc_data_g.datas[SMALL] = malloc_data_g.data_small;
	malloc_data_g.datas_end[SMALL] = malloc_data_g.data_small + size;
	ft_putendl("data_init() OK\n");
	return (M_OK);
}

int		pages_init(void)
{
	if (data_init() == M_OK && metadata_init() == M_OK)
		return (M_OK);
	else
		return (M_NOK);
}
