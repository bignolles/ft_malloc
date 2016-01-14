/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:57:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/14 16:14:25 by marene           ###   ########.fr       */
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
	size_t		k;
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
		tinysize = get_metapagesize(TINY);
		smallsize = get_metapagesize(SMALL);
		while (i < tinysize || j < smallsize) // On verifie que les pages de metadatas on bien ete initialisee a 0
		{
			if (i < tinysize)
			{
				if (*(intptr_t*)(malloc_data_g.meta_tiny + i) != 0)
				{
					*errmsg = ft_strdup("meta_tiny pages are not properly initialized");
					return (UNIT_NOK);
				}
				i += sizeof(intptr_t);
			}
			if (j < smallsize)
			{
				if (*(intptr_t*)(malloc_data_g.meta_small + j) != 0)
				{
					*errmsg = ft_strdup("meta_small pages are not properly initialized");
					return (UNIT_NOK);
				}
				j += sizeof(intptr_t);
			}
		}
		ft_putendl("metadata initial datas integrity OK");
		if ((tinys = malloc(tinysize / sizeof(intptr_t))) == NULL || (smalls = malloc(smallsize / sizeof(intptr_t))) == NULL)
		{
			*errmsg = ft_strdup("Unexpected error!");
			return (UNIT_NOK);
		}
		else
		{
			ft_putendl("tinys and smalls array malloced OK");
			ft_bzero(tinys, tinysize / sizeof(intptr_t));
			ft_bzero(smalls, smallsize / sizeof(intptr_t));
			ft_putendl("tinys and smalls array initialized OK");
			i = 0;
			j = 0;
			while (i < tinysize / sizeof(intptr_t) && j < smallsize / sizeof(intptr_t))
			{ // On remplit les pages tiny ey small de metadata completement, en en enlevant aleatoirement avec des remove()
				if (i < tinysize / sizeof(intptr_t))
				{
					if (rand() % 5 > 0) // 4 chances sur 5 d'effectuer un metadata_add
					{
						ft_putendl("tiny -> metadata_add");
						k = 0;
						while (k < tinysize && tinys[k] != 0)
							++k;
						tinys[k] = malloc(1);
						if (metadata_add(tinys[k], TINY) == M_NOK)
						{
							*errmsg = ft_strdup("metadata_add failed! It must now commit hara kiri!");
							return (UNIT_NOK);
						}
					}
					else
					{
						ft_putendl("tiny -> metadata_remove");
						k = rand() % (tinysize / sizeof(intptr_t));
						while (tinys[k] == NULL)
							k = rand() % (tinysize / sizeof(intptr_t));
						if (metadata_remove(tinys[k], TINY) == M_NOK)
						{
							*errmsg = ft_strdup("metadata_remove failed! It must now commit hara kiri!");
							return (UNIT_NOK);
						}
					}
					++i;
				}
				if (j < smallsize / sizeof(intptr_t))
				{
					if (rand() % 5 > 0) // 4 chances sur 5 d'effectuer un metadata_add
					{
						ft_putendl("small -> metadata_add");
						k = 0;
						while (k < smallsize && smalls[k] != 0)
							++k;
						smalls[k] = malloc(1);
						if (metadata_add(smalls[k], TINY) == M_NOK)
						{
							*errmsg = ft_strdup("metadata_add failed! It must now commit hara kiri!");
							return (UNIT_NOK);
						}
					}
					else
					{
						ft_putendl("small -> metadata_remove");
						k = rand() % (smallsize / sizeof(intptr_t));
						while (smalls[k] == NULL)
							k = rand() % (smallsize / sizeof(intptr_t));
						if (metadata_remove(smalls[k], SMALL) == M_NOK)
						{
							*errmsg = ft_strdup("metadata_remove failed! It must now commit hara kiri!");
							return (UNIT_NOK);
						}
					}
					++j;
				}
			}
			i = 0;
			j = 0;
			while (i < tinysize / sizeof(intptr_t) && j < smallsize / sizeof(intptr_t))
			{
				if (i < tinysize / sizeof(intptr_t))
				{
					if (metadata_retrieve(tinys[i]) != tinys[i] + sizeof(intptr_t) || metadata_remove(tinys[i], TINY) == M_NOK)
					{
						*errmsg = ft_strdup("Something happened during free phase for tiny");
						return (UNIT_NOK);
					}
					else
						free(tinys[i]);
					++i;
				}
				if (i < smallsize / sizeof(intptr_t))
				{
					if (metadata_retrieve(smalls[j]) != smalls[j] + sizeof(intptr_t) || metadata_remove(smalls[j], SMALL) == M_NOK)
					{
						*errmsg = ft_strdup("Something happened during free phase for small");
						return (UNIT_NOK);
					}
					else
						free(smalls[j]);
					++j;
				}
			}
		}
	}
	return (UNIT_OK);
}
