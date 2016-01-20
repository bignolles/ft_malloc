/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:18:11 by marene            #+#    #+#             */
/*   Updated: 2016/01/20 16:33:20 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

metadata_t		malloc_data_g;

void*			alloc(size_t size, blocksize_t blk_size)
{
	void*	data;
	void*	end;
	void*	ret;
	int32_t	len;

	data = malloc_data_g.datas[blk_size];
	end = malloc_data_g.datas_end[blk_size];
	if (size == LARGE)
	{
		ret = mmap(NULL, size + sizeof(int32_t), MMAP_PROT, MMAP_FLAGS, -1, 0);
		if (ret == MAP_FAILED)
			ret = NULL;
		return (ret);
	}
	printf("%zu, %d\n", size, blk_size);
	while (data < end)
	{
		ft_putendl("searching for allocable memory...");
		len = *(int32_t*)data;
		if (len <= 0)
		{
			ft_putendl("\t|-> found some!\n");
			ret = data + sizeof(int32_t);
			if (metadata_add(ret, size) == M_OK)
			{
				*(int32_t*)data = size; // PROBLEME -> On stock la taille comme un int, alors qu'a la base c'est un size_t! :/
				return (data);
			}
			else
				return (NULL);
		}
		else
			data += sizeof(int32_t) + len;
	}
	return (NULL);
}

void*			malloc(size_t size)
{
	static char		init = 0;

	if (!init)
	{
		if (pages_init() == M_OK)
			init = 1;
		else
		{
			ft_putendl("init fail\n");
			return (NULL);
		}
	}
	printf("===== %p =====\n", malloc_data_g.meta_pages_start[TINY]);
	if (size < TINY_MAX_SIZE)
		return (alloc(size, TINY));
	else if (size < SMALL_MAX_SIZE)
		return (alloc(size, SMALL));
	else
		return (alloc(size, LARGE));
}
