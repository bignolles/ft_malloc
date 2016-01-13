/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:02:38 by marene            #+#    #+#             */
/*   Updated: 2016/01/13 14:13:50 by ndatin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <libft.h>
#include <ft_malloc.h>

extern metadata_t	malloc_data_g;

int					metadata_init(void)
{
	int		page_size;

	/**
	 * \fn int metadata_init(void)
	 * \brief cree les pages de metadata 'tiny' et 'small', et memset leurs valeur a 0
	 * \return M_OK si tout c'est bien passe, M_NOK si mmap echoue
	 */
	page_size = getpagesize();
	malloc_data_g.meta_tiny = mmap(NULL, page_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	malloc_data_g.meta_small = mmap(NULL, page_size, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if  (malloc_data_g.meta_tiny != MAP_FAILED && malloc_data_g.meta_small != MAP_FAILED)
	{
		ft_bzero(malloc_data_g.meta_tiny, page_size);
		ft_bzero(malloc_data_g.meta_small, page_size);
		malloc_data_g.meta_pages_start[TINY] = malloc_data_g.meta_tiny;
		malloc_data_g.meta_pages_end[TINY] = malloc_data_g.meta_tiny + page_size - sizeof(void *);
		malloc_data_g.meta_pages_start[SMALL] = malloc_data_g.meta_small;
		malloc_data_g.meta_pages_end[SMALL] = malloc_data_g.meta_small + page_size - sizeof(void *);
		return (M_OK);
	}
	else
		return (M_NOK);
}

void*				metadata_retrieve(void* usr_ptr)
{
	/**
	 * \fn void* metadata_retrieve(void* usr_ptr)
	 * \brief cherche un pointeur
	 */
	return (NULL);
}

int					metadata_add(void *usr_ptr, blocksize_t size)
{
	intptr_t	it;
	intptr_t	end;

	it = (intptr_t)malloc_data_g.meta_pages_start[size];
	end = (intptr_t)malloc_data_g.meta_pages_end[size];
	while (it != end)
	{
		if (!it)
		{
			it = (intptr_t)usr_ptr;
			return (1);
		}
		it++;
	}
	return (0);
}

int					metadata_remove(void *usr_ptr, blocksize_t size)
{
	intptr_t	it;
	intptr_t	end;

	it = (intptr_t)malloc_data_g.meta_pages_start[size];
	end = (intptr_t)malloc_data_g.meta_pages_end[size];
	if ((intptr_t)usr_ptr < it || (intptr_t)usr_ptr > end)
		return (0);
	while (it != end)
	{
		if (it == (intptr_t)usr_ptr)
			it = 0;
		it++;
	}
	return (0);
}
