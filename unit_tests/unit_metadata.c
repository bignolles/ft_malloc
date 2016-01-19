/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:57:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/19 16:35:21 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "unit_tests.h"
#include "ft_malloc.h"

extern metadata_t		malloc_data_g;

void	unit_dump_meta(blocksize_t size)
{
	size_t		it = 0;

	while (it < malloc_data_g.meta_len[size] - 1)
	{
		if (malloc_data_g.meta_pages_start[size][it] != NULL)
			printf("[%zu]\t%p\n", it, malloc_data_g.meta_pages_start[size][it]);
		++it;
	}
}

int		unit_use_retrieve(void** meta, char** errmsg)
{
	size_t		i = 0;

	while (meta[i] != NULL)
	{
		if (meta[i] - sizeof(void*) != metadata_retrieve(meta[i]))
		{
			*errmsg = ft_strdup("metadata_retrieve() failed");
			printf("looking for meta[%zu] : %p (%p)\n", i, meta[i], meta[i] - sizeof(void*));
			printf("____________TINY_____________\n");
			unit_dump_meta(TINY);
			printf("____________SMALL_____________\n");
			unit_dump_meta(SMALL);
			return (UNIT_NOK);
		}
		++i;
	}
	return (UNIT_OK);
}

int		unit_use_remove(void** meta, size_t k, blocksize_t size, char** errmsg)
{
	if (meta[k] == NULL || metadata_remove(meta[k], size) == M_OK)
	{
		meta[k] = NULL;
		return (UNIT_OK);
	}
	else
	{
		unit_dump_meta(size);
		*errmsg = ft_strdup("metadata_remove() failed");
		return (UNIT_NOK);
	}
}

int		unit_use_add(void** meta, size_t metalen, blocksize_t size, char** errmsg)
{
	size_t		i;

	i = 0;
	while (i < metalen - 1  && meta[i] != NULL)
		++i;
	if (i >= metalen - 1)
	{
		printf("i in use_add : %zu\n", i);
		*errmsg = ft_strdup("no more place");
		return (UNIT_NOK);
	}
	if (i < metalen - 1)
	{
		meta[i] = malloc(1);
		if (metadata_add(meta[i], size) == M_OK)
			return (UNIT_OK);
	}
	*errmsg = ft_strdup("metadata_add failed");
	return (UNIT_NOK);
}

int		unit_metadata(char** errmsg)
{
	size_t		i;
	size_t		j;
	size_t		add = 0;
	size_t		delete = 0;
	void**		tinys;
	void**		smalls;

	*errmsg = NULL;
	if (metadata_init() == M_NOK) // On test si l'initialisation des metadatas ne retourne pas une erreur (fail mmap)
	{
		*errmsg = ft_strdup("malloc metadatas initialization failed");
		return (UNIT_NOK);
	}
	else
	{
		ft_putendl("metadata_init() OK");
		i = 0;
		j = 0;
		while (i < malloc_data_g.meta_len[TINY]  - 1 || j < malloc_data_g.meta_len[SMALL] - 1)
		{ // On verifie que les pages de metadatas on bien ete initialisee a 0
			if (i < malloc_data_g.meta_len[TINY] - 1)
			{
				if (malloc_data_g.meta_tiny[i] != NULL)
				{
					*errmsg = ft_strdup("meta_tiny pages are not properly initialized");
					return (UNIT_NOK);
				}
				++i;
			}
			if (j < malloc_data_g.meta_len[SMALL] - 1)
			{
				if (malloc_data_g.meta_pages_start[SMALL][j] != NULL)
				{
					*errmsg = ft_strdup("meta_malloc_data_g.meta_len[SMALL] pages are not properly initialized");
					return (UNIT_NOK);
				}
				++j;
			}
		}
		ft_putendl("metadata initial datas integrity OK");
		if ((tinys = malloc((malloc_data_g.meta_len[TINY] + 1) * sizeof(void*))) == NULL
				|| (smalls = malloc((malloc_data_g.meta_len[SMALL] + 1) * sizeof(void*))) == NULL)
		{
			*errmsg = ft_strdup("Unexpected error!");
			return (UNIT_NOK);
		}
		else
		{
			ft_putendl("tinys and smalls array malloced OK");
			ft_bzero(tinys, malloc_data_g.meta_len[TINY] + 1);
			ft_bzero(smalls, malloc_data_g.meta_len[SMALL] + 1);
			ft_putendl("tinys and smalls array initialized OK");
			i = 0;
			j = 0;
			while (i < malloc_data_g.meta_len[TINY] - 1 || j < malloc_data_g.meta_len[SMALL] - 1)
			{
				++i;
				if (i < malloc_data_g.meta_len[TINY] - 1)
				{
					if (i > 0 && rand() % 5 == 4)
					{
						if (unit_use_remove(tinys, i, TINY, errmsg) == UNIT_NOK)
						{
							return (UNIT_NOK);
						}
						++delete;
						--i;
					}
					else
					{
						if (unit_use_add(tinys, malloc_data_g.meta_len[TINY], TINY, errmsg) == UNIT_NOK)
						{
							return (UNIT_NOK);
						}
						++add;
					}
				}
				if (j < malloc_data_g.meta_len[SMALL] - 1)
				{
					++j;
				}
			}
			if (unit_use_retrieve(tinys, errmsg) == UNIT_NOK || unit_use_retrieve(smalls, errmsg) == UNIT_NOK)
			{
				return (UNIT_NOK);
			}
		}
	}
	return (UNIT_OK);
}
