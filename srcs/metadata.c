/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:02:38 by marene            #+#    #+#             */
/*   Updated: 2016/01/12 16:26:46 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include "libft.h"
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;

int			metadata_init(void)
{
	malloc_data_g.meta_tiny = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	malloc_data_g.meta_small = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return (malloc_data_g.meta_tiny == MAP_FAILED || malloc_data_g.meta_small == MAP_FAILED) ? M_NOK : M_OK;
}

void*		metadata_retrieve(void* usr_ptr)
{
	void*		it_tiny;
	void*		it_small;
	size_t		i;

	if (usr_ptr != NULL)
	{
		usr_ptr -= sizeof(int64_t);
		i = 0;
		it_tiny = malloc_data_g.meta_tiny;
		it_small = malloc_data_g.meta_small;
		while (i <= getpagesize() - sizeof(intptr_t))
		{
			if (i == getpagesize() - sizeof(intptr_t))
			{
				ft_memcpy(&it_tiny, it_tiny, sizeof(intptr_t));
				ft_memcpy(&it_small, it_small, sizeof(intptr_t));
				if (it_tiny == 0 && it_small == 0)
					++i;
				else
					i = 0;
			}
			else
			{
				if ((it_tiny && *(intptr_t*)it_tiny == *(intptr_t*)usr_ptr) || (it_small && *(intptr_t*)it_small == *(intptr_t*)usr_ptr))
				{
					return (usr_ptr);
				}
				it_tiny += sizeof(intptr_t);
				it_small += sizeof(intptr_t);
				i += sizeof(intptr_t);
			}
		}
	}
	return (NULL);
}
