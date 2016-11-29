/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:18:25 by marene            #+#    #+#             */
/*   Updated: 2016/04/21 17:28:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

void		destroy_segment(t_header *head, t_blocksize blk_size)
{
	t_header	*prev;
	t_header	*next;

	HEADER_CONTROL(head, ORIGIN);
	ft_putendl("destroy_segment");
	prev = (head->prev == NULL) ?
		NULL : (t_header*)(head->prev - sizeof(t_header));
	next = (head->next == NULL) ?
		NULL : (t_header*)(head->next - sizeof(t_header));
	if (prev != NULL)
	{
		HEADER_CONTROL(prev, ORIGIN);
		prev->next = next + 1;
	}
	if (next != NULL)
	{
		HEADER_CONTROL(next, ORIGIN);
		next->prev = prev + 1;
	}
	munmap(head, g_malloc_data.datas_len[blk_size] + sizeof(t_header));
}
