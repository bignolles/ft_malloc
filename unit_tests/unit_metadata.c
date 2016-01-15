/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:57:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/15 13:32:50 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "unit_tests.h"
#include "ft_malloc.h"

extern metadata_t		malloc_data_g;

int		unit_metadata(char** errmsg)
{
	size_t		i;
	size_t		j;
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
					if (tinys[i] != NULL && rand() % 5 == 4)
					{
						if (metadata_remove(tinys[i], TINY) == M_NOK)
						{
							ft_putendl("metadata_remove() failed!");
							return (UNIT_NOK);
						}
						else
						{
							free(tinys[i]);
							tinys[i] = NULL;
						}
					}
					else
					{
						tinys[i] = malloc(1);
						metadata_add(tinys[i], TINY);
						++i;
					}
				}
				if (j < smallsize)
				{
					++j;
				}
			}
		}
	}
	return (UNIT_OK);
}
