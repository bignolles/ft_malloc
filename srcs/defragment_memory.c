/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 11:38:23 by marene            #+#    #+#             */
/*   Updated: 2016/04/21 17:08:11 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static void			*frag_regroup(void *it, void **defrag, int32_t frag_size,
		int32_t *total_size)
{
	PROFILE_BASIC;
	if (*defrag == NULL)
	{
		*defrag = it;
		*total_size = -1 * (int32_t)sizeof(int32_t);
	}
	*total_size += (frag_size + (int32_t)sizeof(int32_t));
	it = it + frag_size + sizeof(int32_t);
	return (it);
}

static void			*frag_concat(void *it, void **defrag, int32_t frag_size,
		int32_t *total_size)
{
	PROFILE_BASIC;
	if (*defrag != NULL)
		*(int32_t*)*defrag = -1 * *total_size;
	*defrag = NULL;
	it = it + frag_size + sizeof(int32_t);
	return (it);
}

static int32_t		defrag_it(t_blocksize blk_size, void *data, void *meta_ptr)
{
	void		*it;
	void		*defrag;
	int32_t		size;
	uint8_t		defragged;

	size = 0;
	it = data;
	defragged = 0;
	defrag = NULL;
	while (!defragged && it < data + g_malloc_data.datas_len[blk_size])
	{
		if (*(int32_t*)it <= 0)
			it = frag_regroup(it, &defrag, -1 * *(int32_t*)it, &size);
		else
		{
			it = frag_concat(it, &defrag, *(int32_t*)it, &size);
			if (it > meta_ptr || it >= data + g_malloc_data.datas_len[blk_size])
				return (size);
			size = 0;
		}
	}
	if (defrag != NULL)
		*(int32_t*)defrag = -1 * size;
	return (size);
}

int32_t				defragment_memory(t_blocksize blk_size, void *meta_ptr)
{
	void			*data;
	t_header		*head;
	int32_t			size_defragged;

	PROFILE_BASIC;
	if (blk_size < LARGE)
	{
		data = g_malloc_data.datas[blk_size];
		while (data != NULL)
		{
			head = header_change_segment((t_header**)(&data), SEG_NONE, ORIGIN);
			if (meta_ptr >= data
					&& meta_ptr <= data + g_malloc_data.datas_len[blk_size])
			{
				size_defragged = defrag_it(blk_size, data, meta_ptr);
				return (size_defragged);
			}
			data = header_change_segment(&head, SEG_NEXT, ORIGIN);
		}
	}
	return (0);
}
