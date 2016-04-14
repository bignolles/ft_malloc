/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 13:18:25 by marene            #+#    #+#             */
/*   Updated: 2016/04/14 14:10:31 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		destroy_segment(t_header *head)
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
		prev->next = next;
	}
	if (next != NULL)
	{
		HEADER_CONTROL(next, ORIGIN);
		next->prev = prev;
	}
	return (M_OK);
}
