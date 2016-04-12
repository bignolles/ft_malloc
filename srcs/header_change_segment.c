/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_change_segment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 15:37:37 by marene            #+#    #+#             */
/*   Updated: 2016/04/12 18:13:18 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_malloc.h"

static void		check_header(t_header *head, const char *origin)
{
	PROFILE_BASIC;
	if (head->magic != (M_MAGIC ^ (unsigned long int)head))
	{
		ft_putstr("invalid header at ");
		putaddr((unsigned long int)head, 1);
		ft_putstr(" (header control xor key is : ");
		putaddr((unsigned long int)M_MAGIC, 1);
		ft_putstr(") originated from ");
		ft_putendl(origin);
		exit(42);
	}
}

void			*header_change_segment(t_header **head, t_direction dir,
		const char *origin)
{
	void	*data;

	PROFILE_BASIC;
	data = NULL;
	if (dir == SEG_NONE)
		data = (*head - 1);
	else if (dir == SEG_PREV)
		data = (*head)->prev;
	else if (dir == SEG_NEXT)
		data = (*head)->next;
	if (dir != SEG_NONE && data != NULL)
	{
		HEADER_CONTROL(*head, origin);
		*head = data - sizeof(t_header);
		HEADER_CONTROL(*head, origin);
	}
	else if (data != NULL)
		HEADER_CONTROL(data, origin);
	return (data);
}
