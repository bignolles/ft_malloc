/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbpushback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	cb_push_back(t_cb *cb, const void *item)
{
	if (cb->nb_items == cb->capacity)
		return (0);
	ft_memcpy(cb->first, item, cb->item_size);
	cb->first = (char*)cb->first + cb->item_size;
	if (cb->first == cb->buffer_end)
		cb->first = cb->buffer;
	cb->nb_items++;
	return (1);
}
