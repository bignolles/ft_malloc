/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_adress_validity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 12:06:54 by marene            #+#    #+#             */
/*   Updated: 2016/04/25 15:58:46 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Having to write this function pains me : But the subject of this project
** specifies that one's free and realloc checks if the pointers passed
** as parameters were allocated before doing any treatment.
** Totally buggers the performances of the whole things, and isn't even
** implemented in the reall free and realloc.
** Fuck this shit.
*/

#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static int			check_adress_validity_tinysmall(void *ptr,
		t_blocksize blk_size)
{
	void		*data;
	void		*data_end;
	t_header	*head;
	int			i;
	int32_t		len;

	data = g_malloc_data.datas[blk_size];
	while (data != NULL)
	{
		head = header_change_segment((t_header**)&data, SEG_NONE, ORIGIN);
		data_end = data + g_malloc_data.datas_len[blk_size];
		i = 0;
		while (ptr >= data && ptr <= data_end && data + i < data_end)
		{
			if (data + i == ptr)
				return (M_OK);
			else
			{
				len = ft_abs(*(int32_t*)(data + i));
				i += (len + sizeof(int32_t));
			}
		}
		data = header_change_segment(&head, SEG_NEXT, ORIGIN);
	}
	return (M_NOK);
}

static int			check_adress_validity_large(void *ptr)
{
	int		i;

	i = 0;
	while (g_malloc_data.meta_large && i < g_malloc_data.meta_large_len)
	{
		if (ptr == g_malloc_data.meta_large[i])
			return (M_OK);
		++i;
	}
	return (M_NOK);
}

int					check_adress_validity(void *ptr, t_blocksize blk_size)
{
	if (blk_size == LARGE)
	{
		return (check_adress_validity_large(ptr));
	}
	else
	{
		return (check_adress_validity_tinysmall(ptr, blk_size));
	}
}
