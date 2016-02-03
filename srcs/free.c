/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 12:02:33 by marene            #+#    #+#             */
/*   Updated: 2016/02/03 18:52:25 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

extern metadata_t	malloc_data_g;

static void			defragment_memory( blocksize_t blk_size)
{
	void*		it;
	void*		defrag;
	int			size;

	it = malloc_data_g.datas[blk_size];
	defrag = NULL;
	size = 0;
	while (it < malloc_data_g.datas_end[blk_size])
	{
		if (*(int32_t*)it < 0)
		{
	//		if (defrag == NULL)
	//			defrag = it;
	//		size -= *(int32_t*)it;
			putaddr((unsigned long int))
			it += (-1 * *(int32_t*)it) + sizeof(int32_t);
		}
		if (*(int32_t*)it == 0)
		{
		//	if (defrag == NULL)
		//		defrag = it;
			size += sizeof(int32_t);
			it += sizeof(int32_t);
		}
		else
		{
			if (defrag != NULL)
			{
				*(int32_t*)defrag = -1 * size;
			}
			defrag = NULL;
			size = 0;
			it += *(int32_t*)it + sizeof(int32_t);
		}
	}
}

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
			ft_putendl("adding free space");
			free_space_size += (-1 * *(int32_t*)it);
			it += (*(int32_t*)it * -1) + 1;
		}
		else if (*(int32_t*)it == 0)
		{
			ft_putendl("mkay");
			free_space_size += sizeof(int32_t);
			it += sizeof(int32_t);
		}
		else
		{
			ft_putstr("space freed ");
			putaddr((unsigned long int)meta_ptr + sizeof(int32_t));
			ft_putchar('\n');
			*(int32_t*)meta_ptr = -1 * free_space_size;
			return ; // return debranchant, je trouve ca moche, m'enfin...
		}
	}
	*(int32_t*)meta_ptr = -1 * free_space_size;
}

static blocksize_t	get_blk_size(void* meta_ptr)
{
	if (meta_ptr >= malloc_data_g.datas[TINY] && meta_ptr <= malloc_data_g.datas_end[TINY])
		return (TINY);
	if (meta_ptr >= malloc_data_g.datas[SMALL] && meta_ptr <= malloc_data_g.datas_end[SMALL])
		return (SMALL);
	return (LARGE);
}

void				free(void* usr_ptr)
{
	void*			meta_ptr;
	int				to_unmap;
	int				alloced;
	int				page_size;
	blocksize_t		blk_size;

	ft_putendl("free");
	meta_ptr = usr_ptr - sizeof(int32_t);
	blk_size = get_blk_size(meta_ptr);//*(int32_t*)meta_ptr; // On initialse par defaut a TINY
	if (usr_ptr != NULL && meta_ptr != NULL && *(int32_t*)meta_ptr > 0 && blk_size < LARGE)
	{
		adjust_free_memory_size(meta_ptr, blk_size);
		defragment_memory(blk_size);
		show_alloc_mem();
	}
	else
	{
		ft_putnbr_recursive(*(int32_t*)(meta_ptr), get_mult(*(int32_t*)meta_ptr));
		ft_putchar('\n');
		to_unmap = 0;
		page_size = getpagesize();
		alloced = *(int32_t*)meta_ptr;
		to_unmap = alloced;
		if (alloced % page_size > 0)
			to_unmap += (page_size - (alloced % page_size));
		munmap(usr_ptr, to_unmap);
		//printf("mumap(%p (%d), %d)\n", usr_ptr, *(int32_t*)meta_ptr, to_unmap);
		return ;
	}
}
