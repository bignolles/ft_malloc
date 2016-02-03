/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:15:01 by marene            #+#    #+#             */
/*   Updated: 2016/02/03 12:05:09 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include "libft.h"
#include "ft_malloc.h"

extern metadata_t		malloc_data_g;

static blocksize_t		get_blk_size(size_t size)
{
	if (size <= TINY_MAX_SIZE)
		return (TINY);
	else if (size <= SMALL_MAX_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

static void*			realloc_shrink(void* meta_ptr, size_t old_size, size_t new_size)
{
	int32_t		old_free_size;
	void*		ret;

	old_free_size = *(int32_t*)(meta_ptr + old_size + 1);
	if (get_blk_size(new_size) == get_blk_size(old_size))
	{
		*(int32_t*)meta_ptr = new_size;
		*(int32_t*)(meta_ptr + new_size + 1) = old_free_size + -1 * (old_size - new_size);
		return (meta_ptr + sizeof(int32_t));
	}
	else
	{
		if ((ret = malloc(new_size)) != NULL)
			ft_memcpy(ret, meta_ptr + sizeof(int32_t), new_size);
		free(meta_ptr + sizeof(int32_t));
		return (ret);
	}
}

static void*			realloc_enlarge(void* meta_ptr, size_t old_size, size_t new_size)
{
	void*		ret;
	int32_t		next_zone_size;

	next_zone_size = *(int32_t*)(meta_ptr + old_size + 1);
	if (next_zone_size <= 0 && -1 * next_zone_size >= (int32_t)new_size)
	{
		*(int32_t*)(meta_ptr + old_size + 1) += new_size;
		*(int32_t*)(meta_ptr) = new_size;
		return (meta_ptr + sizeof(int32_t));
	}
	else
	{
		if ((ret = malloc(new_size)) != NULL)
			ft_memcpy(ret, meta_ptr + sizeof(int32_t), old_size);
		free(meta_ptr - sizeof(int32_t));
		return (ret);
	}
}

void*					realloc(void* usr_ptr, size_t size)
{
	void*		meta_ptr;
	int32_t		meta_len;

	if (usr_ptr == NULL)
	{
		return (malloc(size));
	}
	else if (size == 0)
		return (NULL);
	meta_ptr = usr_ptr - sizeof(int32_t);
	meta_len = *(int32_t*)(meta_ptr);
	if (meta_len < (int32_t)size)
	{
		return (realloc_enlarge(meta_ptr, meta_len, size));
	}
	else if (meta_len > (int32_t)size)
	{
		return (realloc_shrink(meta_ptr, meta_len, size));
	}
	return (usr_ptr);
}
