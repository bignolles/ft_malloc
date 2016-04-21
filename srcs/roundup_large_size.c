/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roundup_large_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 18:42:27 by marene            #+#    #+#             */
/*   Updated: 2016/04/21 18:45:09 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_malloc.h"

size_t			roundup_large_size(size_t size)
{
	size_t		i;

	i = 0;
	if (size % getpagesize() == 0)
		return (size);
	while (i * getpagesize() <= size)
		++i;
	return (i * getpagesize());
}
