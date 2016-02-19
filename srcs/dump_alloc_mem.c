/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:44:51 by marene            #+#    #+#             */
/*   Updated: 2016/02/19 14:48:58 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata		g_malloc_data;

static void				adjust_len_and_meta(void *addr, int *len, char *meta)
{
	if (*len == 0 && *meta == 0)
	{
		*len = *(int32_t*)(addr);
		if (*len != 0)
		{
			if (*len != 0)
				ft_putstr((*len > 0) ? CLI_RED : CLI_BLUE);
			*meta = 4;
		}
	}
	if (*len > 0 && *meta == 0)
	{
		ft_putstr(CLI_GREEN);
		--(*len);
	}
	else if (*len < 0 && *meta == 0)
	{
		ft_putstr(CLI_DEFAULT);
		++(*len);
	}
	else if (*meta > 0)
	{
		ft_putstr((*len > 0) ? CLI_RED : CLI_BLUE);
		--(*meta);
	}
}

static void				dump_adress_content(void *addr, void *end,
		int32_t *len, char *meta)
{
	int		i;

	i = 0;
	while (i < DUMP_INC && addr + i < end)
	{
		adjust_len_and_meta(addr + i, len, meta);
		ft_putchar_hex(addr + i);
		ft_putchar(' ');
		ft_putstr(CLI_DEFAULT);
		++i;
	}
}

static void				dump_tiny_small(void *data, void *end)
{
	int			i;
	int32_t		len;
	char		meta;

	i = 0;
	meta = 0;
	len = *(int32_t*)data;
	if (len != 0)
		meta = 4;
	while (data + i < end)
	{
		if (i != DUMP_INC && len == 0 && meta == 0)
		{
			len = *(int32_t*)(data + i);
			if (len != 0)
				meta = 4;
		}
		putaddr((unsigned long int)(data + i));
		ft_putchar('\t');
		dump_adress_content(data + i, end, &len, &meta);
		i += DUMP_INC;
		ft_putchar('\n');
	}
}

static void				dump_large(void)
{
	int		i;
	void	*it;
	int		real_len;
	int		len;

	i = 0;
	while (i < g_malloc_data.meta_large_len)
	{
		it = g_malloc_data.meta_large[i];
		if (it != NULL)
		{
			ft_putendl("-------------------------------------");
			len = *(int32_t*)it;
			real_len = (len / getpagesize() + (len % getpagesize() > 0))
				* getpagesize();
			dump_tiny_small(it, it + real_len);
			ft_putendl("-------------------------------------");
		}
		++i;
	}
}

void					dump_alloc_mem(t_blocksize blk_size)
{
	if (blk_size < LARGE)
		dump_tiny_small(g_malloc_data.datas[blk_size],
				g_malloc_data.datas_end[blk_size]);
	else
		dump_large();
}
