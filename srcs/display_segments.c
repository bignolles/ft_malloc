/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_segments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 15:16:17 by marene            #+#    #+#             */
/*   Updated: 2016/04/18 15:27:41 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

void				display_segments(t_blocksize blk_size)
{
	void		*data;
	t_header	*head;

	if (blk_size != LARGE)
	{
		ft_putendl((blk_size == TINY) ? "___segments TINY___" : "___segments SMALL___");
		data = g_malloc_data.datas[blk_size];
		while (data != NULL)
		{
			head = header_change_segment((t_header**)(&data), SEG_NONE, ORIGIN);
			ft_putstr("segment-{prev : ");
			putaddr((unsigned long int)head->prev, 1);
			ft_putstr(" | current : ");
			ft_putstr(CLI_GREEN);
			putaddr((unsigned long int)head, 1);
			ft_putstr(" -> ");
			putaddr((unsigned long int)data, 1);
			ft_putstr(CLI_DEFAULT);
			ft_putstr(" | next : ");
			putaddr((unsigned long int)head->next, 1);
			ft_putendl("}");
			data = header_change_segment(&head, SEG_NEXT, ORIGIN);
		}
	}
}
