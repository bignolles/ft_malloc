/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/01/22 20:10:11 by marene           ###   ########.fr       */
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
			return; // return debranchant, je trouve ca moche, m'enfin...
		}
	}
}
*/

void				free(void* usr_ptr)
{
	/*
	void*			meta_ptr;
	blocksize_t		blk_size;

	blk_size = TINY; // On initialse par defaut a TINY
	meta_ptr = metadata_retrieve(usr_ptr, &blk_size);
	if (meta_ptr != NULL && *(int32_t*)meta_ptr > 0 && blk_size < LARGE)
	{
		adjust_free_memory_size(meta_ptr, blk_size);
	}
	else
	{
		//munmap le malloc LARGE
		return;
	}
	*/
	if (usr_ptr == NULL)
		exit(42);
	ft_putendl("free");
}
