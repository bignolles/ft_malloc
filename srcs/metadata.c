/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndatin <ndatin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 15:02:38 by marene            #+#    #+#             */
/*   Updated: 2016/01/18 10:41:19 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // <- A desfins de tests, a enlever apres
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <libft.h>
#include <ft_malloc.h>

metadata_t		malloc_data_g; // <- TODO declarer en 'extern', et la declarer 'pour de vrai' dans le fichier qui contiendra la definition de malloc!

size_t				get_metapagesize(blocksize_t size)
{
	/**
	 * \fn static size_t get_metapagesize(blocksize_t size)
	 * \param size page de metadata concernee ('tiny' ou 'small')
	 * \return la taille en byte (octets) de la page de metadata passee en parametre
	 */
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

size_t				get_metapagelen(blocksize_t size)
{
	return (get_metapagesize(size) / sizeof(intptr_t));
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
	malloc_data_g.meta_size_tiny = get_metapagelen(TINY);
	malloc_data_g.meta_size_small = get_metapagelen(SMALL);
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
	if (usr_ptr != NULL && ((meta_ptr >= malloc_data_g.data_tiny && meta_ptr <= malloc_data_g.data_tiny_end)
			|| (meta_ptr >= malloc_data_g.data_small && meta_ptr <= malloc_data_g.data_small_end)))
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
	size_t		it;
	void**		meta;
	void*		meta_ptr;
	size_t		len;

	it = 0;
	len = 0;
	if (usr_ptr == NULL)
		return (M_NOK);
	meta_ptr = usr_ptr - sizeof(void*);
	if (size == TINY)
	{
		meta = malloc_data_g.meta_tiny;
		len = malloc_data_g.meta_size_tiny;
	}
	else if (size == SMALL)
	{
		meta = malloc_data_g.meta_small;
		len = malloc_data_g.meta_size_small;
	}
	while (it < len)
	{
		if (meta[it] == NULL)
		{
			meta[it] = meta_ptr;
			printf("add : [%zu]\t%p\n", it, meta[it]);
			return (M_OK);
		}
		++it;
	}
	return (M_NOK);
}

int					metadata_remove(void *usr_ptr, blocksize_t size)
{
	size_t		it;
	size_t		len;
	void**		meta;
	void*		meta_ptr;

	it = 0;
	len = 0;
	if (size == TINY)
	{
		ft_putendl("remove tiny");
		len = malloc_data_g.meta_size_tiny;
		meta = malloc_data_g.meta_tiny;
	}
	else if (size == SMALL)
	{
		ft_putendl("remove small");
		len = malloc_data_g.meta_size_small;
		meta = malloc_data_g.meta_small;
	}
	meta_ptr = usr_ptr - sizeof(void*);
	while (it < len)
	{
		if (meta[it] == meta_ptr)
		{
			meta[it] = NULL;
			return (M_OK);
		}
		++it;
	}
	return (M_NOK);
}
