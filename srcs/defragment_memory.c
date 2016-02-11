/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 11:38:23 by marene            #+#    #+#             */
/*   Updated: 2016/02/11 18:57:22 by marene           ###   ########.fr       */
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

int32_t				defragment_memory(t_blocksize blk_size)
{
	void			*it;
	void			*defrag;
	int32_t			size;
	int32_t			tmp;

	defrag = NULL;
	size = 0;
	if (blk_size < LARGE)
	{
		it = g_malloc_data.datas[blk_size];
		tmp = 0;
		defrag = NULL;
		while (it < g_malloc_data.datas_end[blk_size])
		{
			tmp = *(int32_t*)it;
			if (tmp <= 0)
				it = frag_regroup(it, &defrag, -1 * tmp, &size);
			else
				it = frag_concat(it, &defrag, tmp, &size);
		}
	}
	if (defrag != NULL)
		*(int32_t*)defrag = -1 * size;
	return (size);
}
