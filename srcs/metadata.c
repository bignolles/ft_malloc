/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:02:38 by marene            #+#    #+#             */
/*   Updated: 2016/01/13 11:00:58 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include "libft.h"
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
		meta_pages_start[TINY] = malloc_data_g.meta_tiny;
		meta_pages_end[TINY] = malloc_data_g.meta_tiny + page_size - sizeof(void *);
		meta_pages_start[SMALL] = malloc_data_g.meta_small;
		meta_pages_end[SMALL] = malloc_data_g.meta_small + page_size - sizeof(void *);
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
	void		*it;
	void		*end;

	it = malloc_meta_g.meta_pages_start[size];
	end = malloc_meta_g.meta_pages_end[size];
	while (it != end)
	{
		if (!it)
		{
			it = usr_ptr;
			return (1);
		}
		it += sizeof(void *);
	}
	return (0);
}
