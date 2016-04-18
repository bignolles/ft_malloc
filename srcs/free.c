/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/04/18 17:10:51 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern t_metadata	g_malloc_data;

static t_blocksize	get_blk_size(void *meta_ptr, t_header **head)
{
	void		*data_tiny;
	void		*data_small;
	t_header	*head_tiny;
	t_header	*head_small;

	PROFILE_BASIC;
	data_tiny = g_malloc_data.datas[TINY];
	data_small = g_malloc_data.datas[SMALL];
	while (data_tiny != NULL || data_small != NULL)
	{
		if (data_tiny != NULL)
		{
			head_tiny = header_change_segment((t_header**)(&data_tiny),
					SEG_NONE, ORIGIN);
			*head = head_tiny;
			if (meta_ptr >= data_tiny
					&& meta_ptr <= data_tiny + g_malloc_data.datas_len[TINY])
				return (TINY);
			data_tiny = header_change_segment(&head_tiny, SEG_NEXT, ORIGIN);
		}
		else if (data_small != NULL)
		{
			head_small = header_change_segment((t_header**)(&data_small),
					SEG_NONE, ORIGIN);
			*head = head_small;
			if (meta_ptr >= data_small
					&& meta_ptr <= data_small + g_malloc_data.datas_len[SMALL])
				return (SMALL);
			data_small = header_change_segment(&head_small, SEG_NEXT, ORIGIN);
		}
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
		if ((alloced = defragment_memory(blk_size, m_ptr)) >= g_malloc_data.max_size[blk_size]
				&& ((void*)head >= g_malloc_data.datas_end[blk_size] || (void*)head < g_malloc_data.datas[blk_size]))
			destroy_segment(head);
	}
	else if (usr_ptr != NULL && m_ptr != NULL && clear_meta(m_ptr) == M_OK)
	{
		alloced = *(int32_t*)m_ptr;
		to_unmap = alloced / getpagesize() + (alloced % getpagesize() > 0);
		munmap(m_ptr, to_unmap * getpagesize());
	}
	CALL_RECORD(NULL);
}
