/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/02/15 12:00:23 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern t_metadata	g_malloc_data;

static t_blocksize	get_blk_size(void *meta_ptr)
{
	if (meta_ptr >= g_malloc_data.datas[TINY]
			&& meta_ptr < g_malloc_data.datas_end[TINY])
	{
		return (TINY);
	}
	else if (meta_ptr >= g_malloc_data.datas[SMALL]
			&& meta_ptr < g_malloc_data.datas_end[SMALL])
	{
		return (SMALL);
	}
	else
	{
		return (LARGE);
	}
}

static void			clear_meta(void *meta_ptr)
{
	int		i;

	i = 0;
	while (g_malloc_data.meta_large[i] != meta_ptr)
		++i; // TODO : risque de segfault si i == max
	g_malloc_data.meta_large[i] = NULL;
}

void				free(void *usr_ptr)
{
	void			*meta_ptr;
	int				to_unmap;
	int				alloced;
	t_blocksize		blk_size;

	meta_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(meta_ptr);
	if (usr_ptr != NULL && meta_ptr != NULL && *(int32_t*)meta_ptr > 0
			&& blk_size < LARGE)
	{
		if (*(int32_t*)meta_ptr > 0)
			*(int32_t*)meta_ptr *= -1;
		defragment_memory(blk_size);
	}
	else if (usr_ptr != NULL)
	{
		alloced = *(int32_t*)meta_ptr;
		to_unmap = alloced / getpagesize() + (alloced % getpagesize() > 0);
		if (munmap(meta_ptr, to_unmap * getpagesize()) == 0)
			clear_meta(meta_ptr);
	}
}
