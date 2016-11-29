/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:15:01 by marene            #+#    #+#             */
/*   Updated: 2016/04/25 15:16:03 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata		g_malloc_data;

static t_blocksize		get_blk_size(size_t size)
{
	PROFILE_BASIC;
	if (size <= TINY_MAX_SIZE)
	{
		return (TINY);
	}
	else if (size <= SMALL_MAX_SIZE)
	{
		return (SMALL);
	}
	else
	{
		return (LARGE);
	}
}

static void				*realloc_shrink(void *meta_ptr, size_t old_size,
		size_t new_size)
{
	int32_t		old_free_size;
	void		*ret;

	PROFILE_BASIC;
	old_free_size = *(int32_t*)(meta_ptr + old_size + 1);
	if (get_blk_size(new_size) == get_blk_size(old_size))
	{
		*(int32_t*)meta_ptr = new_size;
		*(int32_t*)(meta_ptr + new_size + 1) = old_free_size +
			-1 * (old_size - new_size);
		CALL_RECORD(NULL);
		return (meta_ptr + sizeof(int32_t));
	}
	else
	{
		if ((ret = malloc(new_size)) != NULL)
			ft_memcpy(ret, meta_ptr + sizeof(int32_t), new_size);
		free(meta_ptr + sizeof(int32_t));
		CALL_RECORD(NULL);
		return (ret);
	}
}

static void				*enlarge_l2l(void *meta_ptr, size_t old_size,
		size_t new_size)
{
	size_t			page_nb;
	void			*ret;

	PROFILE_BASIC;
	page_nb = old_size / getpagesize();
	if (old_size % getpagesize() > 0)
		++page_nb;
	if (new_size + sizeof(int32_t) <= page_nb * getpagesize())
	{
		*(int32_t*)meta_ptr = new_size;
		CALL_RECORD(NULL);
		return (meta_ptr + sizeof(int32_t));
	}
	else
	{
		ret = malloc(new_size + sizeof(int32_t));
		if (ret != NULL)
		{
			ft_memcpy(ret, meta_ptr + sizeof(int32_t), old_size);
		}
		free(meta_ptr + sizeof(int32_t));
		CALL_RECORD(NULL);
		return (ret);
	}
}

static void				*realloc_enlarge(void *meta_ptr, size_t old_size,
		size_t new_size)
{
	void			*ret;
	int32_t			next_zone_size;

	PROFILE_BASIC;
	if (old_size > SMALL_MAX_SIZE)
		return (enlarge_l2l(meta_ptr, old_size, new_size));
	next_zone_size = *(int32_t*)(meta_ptr + old_size + sizeof(int32_t));
	if (get_blk_size(new_size) == get_blk_size(old_size)
			&& next_zone_size < 0 && -1 * next_zone_size + old_size > new_size)
	{
		*(int32_t*)(meta_ptr) = new_size;
		*(int32_t*)(meta_ptr + new_size + sizeof(int32_t)) =
			(int32_t)new_size - (-1 * next_zone_size + old_size);
		CALL_RECORD(NULL);
		return (meta_ptr + sizeof(int32_t));
	}
	else
	{
		if ((ret = malloc(new_size)) != NULL)
			ft_memcpy(ret, meta_ptr + sizeof(int32_t), old_size);
		free(meta_ptr + sizeof(int32_t));
		CALL_RECORD(NULL);
		return (ret);
	}
}

void					*realloc(void *usr_ptr, size_t size)
{
	void		*meta_ptr;
	int32_t		meta_len;

	PROFILE_BASIC;
	CALL_RECORD(__func__);
	if (usr_ptr == NULL)
	{
		CALL_RECORD(NULL);
		return (malloc(size));
	}
	else if (size == 0)
	{
		CALL_RECORD(NULL);
		return (NULL);
	}
	meta_ptr = usr_ptr - sizeof(int32_t);
	meta_len = *(int32_t*)(meta_ptr);
	if (check_adress_validity(meta_ptr, get_blk_size(meta_len)) == M_NOK)
		return (NULL);
	if (meta_len < (int32_t)size)
		return (realloc_enlarge(meta_ptr, meta_len, size));
	else if (meta_len > (int32_t)size)
		return (realloc_shrink(meta_ptr, meta_len, size));
	CALL_RECORD(NULL);
	return (usr_ptr);
}
