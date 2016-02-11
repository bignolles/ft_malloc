/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:43:53 by marene            #+#    #+#             */
/*   Updated: 2016/02/11 18:57:42 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static void		print_allocated_zone(void *it, int32_t size)
{
	putaddr((uint64_t)(it + sizeof(int32_t)));
	ft_putstr(" - ");
	putaddr((uint64_t)(it + sizeof(int32_t) + size));
	ft_putstr(" : ");
	ft_putnbr_recursive(size, get_mult(size));
	ft_putendl(" octets ");
}

static void		print_tiny_small(char *title, void *it, void *end)
{
	int32_t		size;
	int32_t		total_size;

	ft_putendl("---------------------------------------------------------");
	total_size = 0;
	ft_putstr(title);
	putaddr((unsigned long int)it);
	ft_putstr(" - ");
	putaddr((unsigned long int)end);
	ft_putchar('\n');
	while (it < end - sizeof(int32_t))
	{
		size = 0;
		if (it != NULL)
		{
			size = *(int32_t*)it;
			if (size > 0)
				print_allocated_zone(it, size);
			if (size < 0)
				size *= -1;
		}
		it += (size + sizeof(int32_t));
	}
	ft_putendl("---------------------------------------------------------");
}

static void		print_large(void)
{
	int32_t		len;
	int			i;
	int			max;
	void		*it;

	i = 0;
	max = (LARGE_PAGES_NB * getpagesize()) / sizeof(void*);
	ft_putendl("---------------------------------------------------------");
	ft_putendl("LARGE");
	while (i < max)
	{
		it = g_malloc_data.meta_large[i];
		if (it != NULL)
		{
			len = *(int32_t*)it;
			print_allocated_zone(it, len);
		}
		++i;
	}
	ft_putendl("---------------------------------------------------------");
}

void			show_alloc_mem(void)
{
	if (g_malloc_data.datas[TINY] != NULL)
		print_tiny_small("TINY : ", g_malloc_data.datas[TINY],
				g_malloc_data.datas_end[TINY]);
	if (g_malloc_data.datas[SMALL] != NULL)
		print_tiny_small("SMALL : ", g_malloc_data.datas[SMALL],
				g_malloc_data.datas_end[SMALL]);
	if (g_malloc_data.meta_large != NULL)
		print_large();
}
