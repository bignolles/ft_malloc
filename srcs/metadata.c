/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:02:38 by marene            #+#    #+#             */
/*   Updated: 2016/01/13 18:29:39 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <libft.h>
#include <ft_malloc.h>

metadata_t		malloc_data_g;

static size_t		get_metapagesize(blocksize_t size)
{
	size_t		pagesize;

	pagesize = 0;
	if (size == TINY)
	{
		pagesize = (((TINY_PAGES_NB * getpagesize()) / TINY_ATOMIC) * sizeof(intptr_t));
	}
	else if (size == SMALL)
	{
		pagesize = (((SMALL_PAGES_NB * getpagesize()) / SMALL_ATOMIC) * sizeof(intptr_t));
	}
	return (pagesize);
}

int					metadata_init(void)
{
	int		pagesize_tiny;
	int		pagesize_small;

	/**
	 * \fn int metadata_init(void)
	 * \brief cree les pages de metadata 'tiny' et 'small', et memset leurs valeur a 0
	 * \return M_OK si tout c'est bien passe, M_NOK si mmap echoue
	 */
	pagesize_tiny = get_metapagesize(TINY);
	pagesize_small = get_metapagesize(SMALL);
	malloc_data_g.meta_tiny = mmap(NULL, pagesize_tiny, MMAP_PROT, MMAP_FLAGS, -1, 0);
	malloc_data_g.meta_small = mmap(NULL, pagesize_small, MMAP_PROT, MMAP_FLAGS, -1, 0);
	if  (malloc_data_g.meta_tiny != MAP_FAILED && malloc_data_g.meta_small != MAP_FAILED)
	{
		ft_bzero(malloc_data_g.meta_tiny, pagesize_tiny);
		ft_bzero(malloc_data_g.meta_small, pagesize_small);
		malloc_data_g.meta_pages_start[TINY] = malloc_data_g.meta_tiny;
		malloc_data_g.meta_pages_end[TINY] = malloc_data_g.meta_tiny + pagesize_tiny - sizeof(void *);
		malloc_data_g.meta_pages_start[SMALL] = malloc_data_g.meta_small;
		malloc_data_g.meta_pages_end[SMALL] = malloc_data_g.meta_small + pagesize_small - sizeof(void *);
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
	void*		meta_ptr;

	meta_ptr = usr_ptr - sizeof(intptr_t);
	if ((meta_ptr >= malloc_data_g.data_tiny && meta_ptr <= malloc_data_g.data_tiny_end)
			|| (meta_ptr >= malloc_data_g.data_small && meta_ptr <= malloc_data_g.data_small_end))
	{
		return (meta_ptr);
	}
	else
	{
		return (NULL);
	}
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
