/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 11:38:23 by marene            #+#    #+#             */
/*   Updated: 2016/02/04 17:03:39 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;

void				defragment_memory(blocksize_t blk_size)
{
	void*		it;
	void*		defrag;
	int32_t		size;
	int32_t		tmp;

	if (blk_size < LARGE)
	{
		it = malloc_data_g.datas[blk_size];
		size = 0;
		tmp = 0;
		defrag = NULL;
		while (it < malloc_data_g.datas_end[blk_size])
		{
			tmp = *(int32_t*)it;
			if (tmp < 0)
			{
				tmp *= -1;
				if (defrag == NULL)
				{
					defrag = it;
					size = -1 * (int32_t)sizeof(int32_t);
				}
				size += (tmp + (int32_t)sizeof(int32_t));
				it = it + tmp + sizeof(int32_t);
			}
			else if (tmp > 0)
			{
				if (defrag != NULL)
				{
					*(int32_t*)defrag = -1 * size;
				}
				defrag = NULL;
				size = 0;
				it = it + tmp + sizeof(int32_t);
			}
			else
				return;
		}
	}
}
