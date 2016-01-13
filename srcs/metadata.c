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
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;

int					metadata_init(void)
{
	/**
	 * \fn int metadata_init(void)
	 * \brief cree les pages de metadata 'tiny' et 'small', et memset leurs valeur a 0
	 * \return M_OK si tout c'est bien passe, M_NOK si mmap echoue
	 */
	malloc_data_g.meta_tiny = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	malloc_data_g.meta_small = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if  (malloc_data_g.meta_tiny != MAP_FAILED && malloc_data_g.meta_small != MAP_FAILED)
	{
		ft_memset(malloc_data_g.meta_tiny, 0, getpagesize());
		ft_memset(malloc_data_g.meta_small, 0, getpagesize());
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

static void*		get_metapage(blocksize_t size)
{
	if (size == TINY)
		return (malloc_meta_g.meta_tiny);
	else if (size == SMALL)
		return (malloc_meta_g.meta_small);
	else if (size == LARGE)
		return (malloc_meta_g.meta_large);
}

int					metadata_add(void* meta_ptr, blocksize_t size)
{
	void		*meta_iterator;
	intptr_t	i;

	meta_iterator = get_metapage(size);
	i = 0;
	while (i < getpagesize() - sizeof())
	{
		if ()
	}
}
