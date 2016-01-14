/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbpopfront.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	cb_pop_front(t_cb *cb, void *item)
{
	if (cb->nb_items == 0)
		return (0);
	ft_memcpy(item, cb->last, cb->item_size);
	cb->last = (char*)cb->last + cb->item_size;
	if (cb->last == cb->buffer_end)
		cb->last = cb->buffer;
	cb->nb_items--;
	return (1);
}
