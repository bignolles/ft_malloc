/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:18:25 by marene            #+#    #+#             */
/*   Updated: 2016/04/18 17:24:03 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

void		destroy_segment(t_header *head)
{
	t_header	*prev;
	t_header	*next;

	HEADER_CONTROL(head, ORIGIN);
	prev =
		(head->prev == NULL) ? NULL : (t_header*)(head->prev - sizeof(t_header));
	next =
		(head->next == NULL) ? NULL : (t_header*)(head->next - sizeof(t_header));
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
	//munmap head
}
