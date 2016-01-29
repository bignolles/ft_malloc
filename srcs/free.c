/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/01/29 16:16:26 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;

/*
static void			adjust_free_memory_size(void* meta_ptr, blocksize_t blk_size)
{
	int		free_space_size;
	void*	it;

	free_space_size = *(int32_t*)meta_ptr;
	it = meta_ptr + free_space_size + sizeof(int32_t);
	while (it < malloc_data_g.datas_end[blk_size])
	{ // Je suis pas tout a fait sur que faire un while pour checker TOUTES la plage de data soit necessaire...
		if (*(int32_t*)it < 0)
		{
			free_space_size += (-1 * *(int32_t*)it);
			it += (*(int32_t*)it * -1) + sizeof(int32_t);
		}
		else
		{
			*(int32_t*)meta_ptr = free_space_size;
			return; // return debranchant, je trouve ca moche, m'enfin...
		}
	}
}
*/

static blocksize_t	free_get_blk_size(void* usr_ptr)
{
	if (usr_ptr >= malloc_data_g.datas[TINY] && usr_ptr <= malloc_data_g.datas_end[TINY])
		return (TINY);
	else if (usr_ptr >= malloc_data_g.datas[SMALL] && usr_ptr <= malloc_data_g.datas_end[SMALL])
		return (SMALL);
	return (LARGE);
}

void				free(void* usr_ptr)
{
	void*			meta_ptr;
	blocksize_t		blk_size;

	return;
	blk_size = free_get_blk_size(usr_ptr); // On initialse par defaut a TINY
	meta_ptr = usr_ptr - sizeof(int32_t);
	if (usr_ptr != NULL && meta_ptr != NULL && *(int32_t*)meta_ptr > 0 && blk_size < LARGE)
	{
		*(int32_t*)meta_ptr *= -1;
		//adjust_free_memory_size(meta_ptr, blk_size);
		//// ^ Je vire temporairement la defragmentation memoire, pour eliminer une possible source de bug
	}
	else
	{
		//munmap le malloc LARGE
		return;
	}
}
