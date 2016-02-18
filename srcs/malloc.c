/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:18:11 by marene            #+#    #+#             */
/*   Updated: 2016/02/18 17:37:46 by marene           ###   ########.fr       */
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
	int		i;

	i = 0;
	while (i < g_malloc_data.meta_large_len
			&& g_malloc_data.meta_large[i] != NULL)
		++i;
	if (g_malloc_data.meta_large_len > i)
	{
		ret = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
		if (ret != MAP_FAILED)
		{
			*(int32_t*)ret = (int32_t)size;
			g_malloc_data.meta_large[i] = ret;
			return (ret + sizeof(int32_t));
		}
	}
	return (NULL);
}

static void			*alloc_tiny_small(void *new_meta, int32_t meta_len,
		int32_t size)
{
	*(int32_t*)new_meta = size;
	if (meta_len != 0 && -1 * meta_len > (int32_t)(size + sizeof(int32_t)))
	{
		*(int32_t*)(new_meta + sizeof(int32_t) + size) =
			meta_len + size + sizeof(int32_t);
	}
	return (new_meta + sizeof(int32_t));
}

static void			*alloc(size_t size, t_blocksize blk_size)
{
	int		i;
	int32_t	len;
	void	*data;
	void	*data_end;

	i = 0;
	if (blk_size == LARGE)
		return (alloc_large(size));
	data = g_malloc_data.datas[blk_size];
	data_end = g_malloc_data.datas_end[blk_size];
	len = 0;
	while (data + i < data_end)
	{
		len = *(int32_t*)(data + i);
		if (len > 0)
			i += len + sizeof(int32_t);
		else if ((len == 0 && data + i + sizeof(int32_t) + size <= data_end)
				|| -1 * len >= (int32_t)(size + sizeof(int32_t)))
		{
			return (alloc_tiny_small(data + i, len, (int32_t)size));
		}
		else
			i += (-1 * len) + sizeof(int32_t);
	}
	return (NULL);
}

static t_blocksize	get_blk_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
	{
		return (TINY);
	}
	else if (size <= SMALL_MAX_SIZE)
	{
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
	static int		init[3] = {0, 0};

	if (size != 0)
	{
		blk_size = get_blk_size(size);
		if (init[blk_size] == 0
				|| (blk_size < LARGE && g_malloc_data.datas[blk_size] == NULL))
		{
			if (pages_init(blk_size) == M_OK)
			{
				init[blk_size] = 1;
			}
			else
				return (NULL);
		}
		return (alloc(size, blk_size));
	}
	else
		return (NULL);
}
