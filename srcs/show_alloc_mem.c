/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:43:53 by marene            #+#    #+#             */
/*   Updated: 2016/02/24 18:44:53 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

static void		print_allocated_zone(void *it, int32_t size, int fd)
{
	int			free;

	free = (size < 0) ? 1 : 0;
	if (free)
		size *= -1;
	putaddr((uint64_t)(it + sizeof(int32_t)), fd);
	ft_putstr_fd(" - ", fd);
	putaddr((uint64_t)(it + sizeof(int32_t) + size), fd);
	ft_putstr_fd(" : ", fd);
	ft_putnbr_recursive(size, get_mult(size), fd);
	ft_putstr_fd(" octets ", fd);
	if (free)
		ft_putendl_fd(" libres", fd);
	else
		ft_putendl_fd(" alloues", fd);
	(void)it;
	(void)size;
	(void)fd;
}

static void		print_tiny_small(char *title, void *it, void *end, int fd)
{
	int32_t		size;
	int32_t		total_size;

	ft_putendl_fd("------------------------------------------------------", fd);
	total_size = 0;
	ft_putstr_fd(title, fd);
	putaddr((unsigned long int)it, fd);
	ft_putstr_fd(" - ", fd);
	putaddr((unsigned long int)end, fd);
	ft_putchar_fd('\n', fd);
	while (it < end - sizeof(int32_t))
	{
		size = 0;
		if (it != NULL)
		{
			size = *(int32_t*)it;
			if (size != 0)
				print_allocated_zone(it, size, fd);
			if (size < 0)
				size *= -1;
		}
		it += (size + sizeof(int32_t));
	}
	ft_putendl_fd("------------------------------------------------------", fd);
}

static void		print_large(int fd)
{
	int32_t		len;
	int			i;
	int			max;
	void		*it;

	i = 0;
	max = (LARGE_PAGES_NB * getpagesize()) / sizeof(void*);
	ft_putendl_fd("------------------------------------------------------", fd);
	ft_putendl_fd("LARGE", fd);
	while (i < max)
	{
		it = g_malloc_data.meta_large[i];
		if (it != NULL)
		{
			len = *(int32_t*)it;
			print_allocated_zone(it, len, fd);
		}
		++i;
	}
	ft_putendl_fd("------------------------------------------------------", fd);
}

void			display_allocs(int fd)
{
	if (g_malloc_data.datas[TINY] != NULL)
		print_tiny_small("TINY : ", g_malloc_data.datas[TINY],
				g_malloc_data.datas_end[TINY], fd);
	if (g_malloc_data.datas[SMALL] != NULL)
		print_tiny_small("SMALL : ", g_malloc_data.datas[SMALL],
				g_malloc_data.datas_end[SMALL], fd);
	if (g_malloc_data.meta_large != NULL)
		print_large(fd);
}

void			show_alloc_mem(void)
{
	display_allocs(1);
}
