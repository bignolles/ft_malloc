/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:57:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/14 11:20:56 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unit_tests.h"
#include "ft_malloc.h"

extern metadata_t		malloc_data_g;

int		unit_metadata(char** errmsg)
{
	*errmsg = NULL;

	if (metadata_init() == M_NOK)
	{
		*errmsg = ft_strdup("malloc metadatas initialization failed");
		return (UNIT_NOK);
	}
	return (UNIT_OK);
}
