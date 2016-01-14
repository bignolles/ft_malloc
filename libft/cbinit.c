/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	cb_init(t_cb *cb, size_t capacity, size_t size)
{
	cb->buffer = malloc(capacity * size);
	if (!cb->buffer)
		return (0);
	cb->buffer_end = (char *)cb->buffer + (capacity * size);
	cb->capacity = capacity;
	cb->nb_items = 0;
	cb->item_size = size;
	cb->first = cb->buffer;
	cb->last = cb->buffer;
	return (1);
}
