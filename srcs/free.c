/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/02/19 17:32:32 by marene           ###   ########.fr       */
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

static int			clear_meta(void *meta_ptr)
{
	int		i;

	i = 0;
	while (i < g_malloc_data.meta_large_len
			&& g_malloc_data.meta_large[i] != meta_ptr)
		++i;
	if (i < g_malloc_data.meta_large_len)
	{
		g_malloc_data.meta_large[i] = NULL;
		return (M_OK);
	}
	return (M_NOK);
}

void				free(void *usr_ptr)
{
	void			*meta_ptr;
	int				to_unmap;
	int				alloced;
	t_blocksize		blk_size;

	meta_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(meta_ptr);
	if (blk_size < LARGE && usr_ptr != NULL && meta_ptr != NULL
			&& *(int32_t*)meta_ptr > 0)
	{
		if (*(int32_t*)meta_ptr > 0)
			*(int32_t*)meta_ptr *= -1;
		defragment_memory(blk_size);
	}
	else if (usr_ptr != NULL && meta_ptr != NULL && clear_meta(meta_ptr) == M_OK)
	{
		alloced = *(int32_t*)meta_ptr;
		to_unmap = alloced / getpagesize() + (alloced % getpagesize() > 0);
		munmap(meta_ptr, to_unmap * getpagesize());
	}
}
