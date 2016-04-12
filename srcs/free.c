/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/04/11 16:17:13 by marene           ###   ########.fr       */
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
	PROFILE_BASIC;
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

	PROFILE_BASIC;
	CALL_RECORD(__func__);
	m_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(m_ptr);
	if (blk_size < LARGE && usr_ptr != NULL && m_ptr != NULL
			&& *(int32_t*)m_ptr > 0)
	{
		if (*(int32_t*)m_ptr > 0)
			*(int32_t*)m_ptr *= -1;
		defragment_memory(blk_size, m_ptr);
	}
	else if (usr_ptr != NULL && m_ptr != NULL && clear_meta(m_ptr) == M_OK)
	{
		alloced = *(int32_t*)m_ptr;
		to_unmap = alloced / getpagesize() + (alloced % getpagesize() > 0);
		munmap(m_ptr, to_unmap * getpagesize());
	}
	CALL_RECORD(NULL);
}
