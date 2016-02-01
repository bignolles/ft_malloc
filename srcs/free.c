/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/01/27 16:36:59 by ndatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern metadata_t	malloc_data_g;

static void			adjust_free_memory_size(void* meta_ptr, blocksize_t blk_size)
{
	int		free_space_size;
	void*	it;

	free_space_size = *(int32_t*)meta_ptr;
	it = meta_ptr + free_space_size + 1;
	while (it < malloc_data_g.datas_end[blk_size])
	{ // Je suis pas tout a fait sur que faire un while pour checker TOUTES la plage de data soit necessaire...
		if (*(int32_t*)it < 0)
		{
			free_space_size += (-1 * *(int32_t*)it);
			it += (*(int32_t*)it * -1) + 1;
		}
		else
		{
			*(int32_t*)meta_ptr = free_space_size;
			return ; // return debranchant, je trouve ca moche, m'enfin...
		}
	}
}

void				free(void* usr_ptr)
{
	void*			meta_ptr;
	int				to_unmap;
	int				ptr_size;
	blocksize_t		blk_size;

	blk_size = TINY; // On initialse par defaut a TINY
	meta_ptr = usr_ptr - sizeof(int32_t);
	if (usr_ptr != NULL && meta_ptr != NULL && *(int32_t*)meta_ptr > 0 && blk_size < LARGE)
	{
		adjust_free_memory_size(meta_ptr, blk_size);
	}
	else
	{
		ptr_size = *(int32_t*)usr_ptr + sizeof(int32_t);
		to_unmap = (getpagesize() % ptr_size) * getpagesize();
		munmap(usr_ptr, to_unmap);
		//printf("munmap(%p, %d)\n", usr_ptr, to_unmap);
		//munmap le malloc LARGE
		return ;
	}
}
