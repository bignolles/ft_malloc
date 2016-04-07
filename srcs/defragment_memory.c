/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 11:38:23 by marene            #+#    #+#             */
/*   Updated: 2016/04/07 15:48:02 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static void			*frag_regroup(void *it, void **defrag, int32_t frag_size,
		int32_t *total_size)
{
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
	if (*defrag != NULL)
		*(int32_t*)*defrag = -1 * *total_size;
	*defrag = NULL;
	*total_size = 0;
	it = it + frag_size + sizeof(int32_t);
	return (it);
}

int32_t				defragment_memory(t_blocksize blk_size, void *meta_ptr)
{
	void			*it;
	void			*defrag;
	void			*data;
	t_header		*head;
	int32_t			size;

	defrag = NULL;
	size = 0;
	data = g_malloc_data.datas[blk_size];
	if (blk_size < LARGE)
	{
		while (data != NULL)
		{
			head = header_change_segment((t_header**)(&data), SEG_NONE, ORIGIN);
			it = data;
			defrag = NULL;
			while (it < data + g_malloc_data.datas_len[blk_size])
			{
				if (*(int32_t*)it <= 0)
					it = frag_regroup(it, &defrag, -1 * *(int32_t*)it, &size);
				else
				{
					it = frag_concat(it, &defrag, *(int32_t*)it, &size);
					if (it > meta_ptr)
						return (M_OK);
				}
			}
			data = header_change_segment(&head, SEG_NEXT, ORIGIN);
		}
	}
	if (defrag != NULL)
		*(int32_t*)defrag = -1 * size;
	return (size);
}
