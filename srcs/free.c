/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/02/10 15:20:48 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern metadata_t	malloc_data_g;

static blocksize_t	get_blk_size(void* meta_ptr)
{
	int32_t		size;

	size = *(int32_t*)meta_ptr;
	if (size <= TINY_MAX_SIZE)
		return (TINY);
	if (size <= SMALL_MAX_SIZE)
		return (SMALL);
	return (LARGE);
}

void				free(void* usr_ptr)
{
	void*			meta_ptr;
	int				to_unmap;
	int				alloced;
	int				i;
	blocksize_t		blk_size;

	i = 0;
	meta_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(meta_ptr);//*(int32_t*)meta_ptr; // On initialse par defaut a TINY
	if (usr_ptr != NULL && meta_ptr != NULL && *(int32_t*)meta_ptr > 0 && blk_size < LARGE)
	{
		if (*(int32_t*)meta_ptr > 0)
			*(int32_t*)meta_ptr *= -1;
		defragment_memory(blk_size);
	}
	else
	{
		to_unmap = 0;
		alloced = *(int32_t*)meta_ptr;
		to_unmap = (alloced / getpagesize() + (alloced % getpagesize() > 0)) * getpagesize();
		if (munmap(meta_ptr, to_unmap) != 0)
		{
			ft_putendl("freeing LARGE malloc miserably failed");
			exit(42);
			// ololol
		}
		while (malloc_data_g.meta_large[i] != meta_ptr)
			++i; // TODO : risque de segfault si i == max
		malloc_data_g.meta_large[i] = NULL;
	}
}
