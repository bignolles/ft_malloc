/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_allocable_segment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 17:17:24 by marene            #+#    #+#             */
/*   Updated: 2016/04/07 17:15:02 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

void				*extend_blk(t_blocksize blk_size, t_header *head)
{
	void		*new_data;
	int			size;
	int			pagesize;

	ft_putendl("_extend_blk");
	pagesize = getpagesize();
	size = (blk_size == TINY) ? TINY_PAGES_NB * pagesize : SMALL_PAGES_NB * pagesize;
	new_data = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if (new_data == MAP_FAILED)
		return (NULL);
	ft_bzero(new_data, size);	
	((t_header*)new_data)->magic = M_MAGIC ^ (unsigned long int)new_data;
	((t_header*)new_data)->prev = (void*)(head + sizeof(t_header));
	((t_header*)new_data)->next = NULL;
	head->next = new_data + sizeof(t_header);
	return (new_data + sizeof(t_header));
}

void				*find_allocable_segment(size_t size, t_blocksize blk_size)
{
	void		*data;
	void		*data_end;
	int			i;
	int			len;
	t_header	*head;

	data = g_malloc_data.datas[blk_size];
	data_end = g_malloc_data.datas_end[blk_size];
	while (data != NULL)
	{
		head = header_change_segment((t_header**)&data, SEG_NONE, ORIGIN);
		i = 0;
		while (data + i < data_end)
		{
			len = *(int32_t*)(data + i);
			if (len > 0)
				i += len + sizeof(int32_t);
			else if ((len == 0 && data + i + sizeof(int32_t) + size <= data_end)
					|| -1 * len > (int32_t)(size + sizeof(int32_t)))
			{
				return (data + i);
			}
			else
				i += (-1 * len) + sizeof(int32_t);
		}
		data = header_change_segment(&head, SEG_NEXT, ORIGIN);
		data_end = data + g_malloc_data.datas_len[blk_size];
	}
	return (extend_blk(blk_size, head));
}
