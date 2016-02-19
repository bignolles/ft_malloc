/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 10:44:51 by marene            #+#    #+#             */
/*   Updated: 2016/02/19 13:50:54 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_malloc.h"

extern t_metadata		g_malloc_data;

static void				dump_adress_content(void *addr, void *end, int32_t *len, char *meta)
{
	int		i;

	i = 0;
	while (i < DUMP_INC && addr + i < end)
	{
		if (*len == 0 && *meta == 0)
		{
			*len = *(int32_t*)(addr + i);
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
			meta = 4;
		}
		putaddr((unsigned long int)(data + i));
		ft_putchar('\t');
		dump_adress_content(data + i, end, &len, &meta);
		i += DUMP_INC;
		ft_putchar('\n');
	}
}

void					dump_alloc_mem(t_blocksize blk_size)
{
	if (blk_size < LARGE)
		dump_tiny_small(g_malloc_data.datas[blk_size],
				g_malloc_data.datas_end[blk_size]);
	else
		dump_tiny_small(NULL, NULL);
}
