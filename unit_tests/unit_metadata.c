/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:57:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/15 15:54:32 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "unit_tests.h"
#include "ft_malloc.h"

extern metadata_t		malloc_data_g;

int		unit_use_remove(void** meta, size_t k, blocksize_t size, char** errmsg)
{
	if (meta[k] == NULL || metadata_remove(meta[k], size) == M_OK)
	{
		return (UNIT_OK);
	}
	else
	{
		*errmsg = ft_strdup("metadata_remove() failed");
		return (UNIT_NOK);
	}
}

int		unit_use_add(void** meta, size_t metalen, blocksize_t size, char** errmsg)
{
	size_t		i;

	i = 0;
	while (i < metalen && meta[i] != NULL)
		++i;
	if (i < metalen)
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
	size_t		tinysize;
	size_t		smallsize;
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
		tinysize = get_metapagelen(TINY);
		smallsize = get_metapagelen(SMALL);
		while (i < tinysize || j < smallsize) // On verifie que les pages de metadatas on bien ete initialisee a 0
		{
			if (i < tinysize)
			{
				if (malloc_data_g.meta_tiny[i] != NULL)
				{
					*errmsg = ft_strdup("meta_tiny pages are not properly initialized");
					return (UNIT_NOK);
				}
				++i;
			}
			if (j < smallsize)
			{
				if (malloc_data_g.meta_small[j] != NULL)
				{
					*errmsg = ft_strdup("meta_small pages are not properly initialized");
					return (UNIT_NOK);
				}
				++j;
			}
		}
		ft_putendl("metadata initial datas integrity OK");
		if ((tinys = malloc(tinysize * sizeof(void*))) == NULL || (smalls = malloc(smallsize * sizeof(void*))) == NULL)
		{
			*errmsg = ft_strdup("Unexpected error!");
			return (UNIT_NOK);
		}
		else
		{
			ft_putendl("tinys and smalls array malloced OK");
			ft_bzero(tinys, tinysize);
			ft_bzero(smalls, smallsize);
			ft_putendl("tinys and smalls array initialized OK");
			i = 0;
			j = 0;
			while (i < tinysize || j < smallsize)
			{
				if (i < tinysize)
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
						if (unit_use_add(tinys, tinysize, TINY, errmsg) == UNIT_NOK)
						{
							return (UNIT_NOK);
						}
						++add;
						++i;
					}
				}
				if (j < smallsize)
				{
					++j;
				}
			}
			printf("Filling tinys and smalls: OK (%zu additions, %zu deletions)\n", add, delete);
		}
	}
	return (UNIT_OK);
}
