/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:18:11 by marene            #+#    #+#             */
/*   Updated: 2016/04/21 18:46:28 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static void			*alloc_large(size_t size)
{
	void	*ret;
	size_t	to_mmap;
	int		i;

	PROFILE_BASIC;
	i = 0;
	to_mmap = roundup_large_size(size);
	while (i < g_malloc_data.meta_large_len
			&& g_malloc_data.meta_large[i] != NULL)
		++i;
	if (g_malloc_data.meta_large_len > i)
	{
		ret = mmap(0, to_mmap, MMAP_PROT, MMAP_FLAGS, -1, 0);
		if (ret != MAP_FAILED)
		{
			*(int32_t*)ret = (int32_t)size;
			g_malloc_data.meta_large[i] = ret;
			CALL_RECORD(ORIGIN);
			return (ret + sizeof(int32_t));
		}
	}
	CALL_RECORD(ORIGIN);
	return (NULL);
}

static void			*alloc_tiny_small(void *new_meta, int32_t meta_len,
		int32_t size)
{
	PROFILE_BASIC;
	*(int32_t*)new_meta = size;
	if (meta_len < 0 && -1 * meta_len > (int32_t)(size + sizeof(int32_t)))
	{
		*(int32_t*)(new_meta + sizeof(int32_t) + size) =
			meta_len + size + sizeof(int32_t);
	}
	CALL_RECORD(ORIGIN);
	return (new_meta + sizeof(int32_t));
}

static void			*alloc(size_t size, t_blocksize blk_size)
{
	int32_t		len;
	void		*new_meta;

	PROFILE_BASIC;
	if (blk_size == LARGE)
		return (alloc_large(size));
	new_meta = find_allocable_segment(size, blk_size);
	if (new_meta != NULL)
	{
		len = *(int32_t*)new_meta;
		return (alloc_tiny_small(new_meta, len, (int32_t)size));
	}
	CALL_RECORD(ORIGIN);
	return (NULL);
}

static t_blocksize	get_blk_size(size_t *size)
{
	PROFILE_BASIC;
	if (*size <= TINY_MAX_SIZE)
	{
		if (*size < TINY_ATOMIC)
			*size = TINY_ATOMIC;
		else if (*size % TINY_ATOMIC != 0)
			*size = TINY_ATOMIC * (*size / TINY_ATOMIC) + TINY_ATOMIC;
		return (TINY);
	}
	else if (*size <= SMALL_MAX_SIZE)
	{
		if (*size < SMALL_ATOMIC)
			*size = SMALL_ATOMIC;
		else if (*size % SMALL_ATOMIC != 0)
			*size = SMALL_ATOMIC * (*size / SMALL_ATOMIC) + SMALL_ATOMIC;
		return (SMALL);
	}
	else
	{
		return (LARGE);
	}
}

void				*malloc(size_t size)
{
	t_blocksize		blk_size;

	PROFILE_BASIC;
	if (size != 0)
	{
		blk_size = get_blk_size(&size);
		if (g_malloc_data.init[blk_size] == 0
				|| (blk_size < LARGE && g_malloc_data.datas[blk_size] == NULL))
		{
			if (pages_init(blk_size) == M_OK)
			{
				record_allocations_init();
				g_malloc_data.init[blk_size] = 1;
			}
			else
			{
				return (NULL);
			}
		}
		return (alloc(size, blk_size));
	}
	else
		return (NULL);
}
