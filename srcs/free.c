/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/04/21 18:35:13 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern t_metadata	g_malloc_data;

static t_blocksize	get_blk_size(void *m_ptr, t_header **head)
{
	void		*data;
	t_header	*h;
	t_blocksize	blk_size;

	PROFILE_BASIC;
	blk_size = TINY;
	data = g_malloc_data.datas[TINY];
	while (data != NULL)
	{
		while (data != NULL)
		{
			h = header_change_segment((t_header**)(&data),
					SEG_NONE, ORIGIN);
			*head = h;
			if (m_ptr >= data &&
					m_ptr <= data + g_malloc_data.datas_len[blk_size])
				return (blk_size);
			data = header_change_segment(&h, SEG_NEXT, ORIGIN);
		}
		data = (blk_size == TINY) ? g_malloc_data.datas[SMALL] : NULL;
		blk_size = SMALL;
	}
	return (LARGE);
}

static int			clear_meta(void *meta_ptr)
{
	int		i;

	PROFILE_BASIC;
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

static void			check_for_destroy(t_blocksize blk_size, void *m_ptr,
		t_header *head)
{
	int				alloced;

	if ((alloced = defragment_memory(blk_size, m_ptr)) >=
			g_malloc_data.max_size[blk_size] &&
			((void*)head >= g_malloc_data.datas[blk_size] +
			g_malloc_data.datas_len[blk_size]
			|| (void*)head < g_malloc_data.datas[blk_size] - sizeof(t_header)))
		destroy_segment(head, blk_size);
}

void				free(void *usr_ptr)
{
	void			*m_ptr;
	int				to_unmap;
	int				alloced;
	t_blocksize		blk_size;
	t_header		*head;

	PROFILE_BASIC;
	CALL_RECORD(__func__);
	head = NULL;
	m_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(m_ptr, &head);
	if (blk_size < LARGE && usr_ptr != NULL && m_ptr != NULL
			&& *(int32_t*)m_ptr > 0)
	{
		if (*(int32_t*)m_ptr > 0)
			*(int32_t*)m_ptr *= -1;
		check_for_destroy(blk_size, m_ptr, head);
	}
	else if (usr_ptr != NULL && m_ptr != NULL && clear_meta(m_ptr) == M_OK)
	{
		alloced = *(int32_t*)m_ptr;
		to_unmap = alloced / getpagesize() + (alloced % getpagesize() > 0);
		munmap(m_ptr, to_unmap * getpagesize());
	}
	CALL_RECORD(NULL);
}
