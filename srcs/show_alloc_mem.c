/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:43:53 by marene            #+#    #+#             */
/*   Updated: 2016/02/09 19:35:45 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_malloc.h"

extern metadata_t	malloc_data_g;
extern size_t		alloc_maxsize_g;

void	putaddr(unsigned long int n)
{
	static char		base16[16];
	char			res[18];
	int				i;

	ft_strcpy(base16, "0123456789abcdef");
	ft_memset(res, '0', 18);
	res[0] = '0';
	res[1] = 'x';
	i = 16 - 1;
	while (n > 0)
	{
		res[i] = base16[n % 16];
		n = n - (n % 16);
		n /= 16;
		i--;
	}
	write(1, res, 16);
}

int				ft_putnbr_recursive(int32_t nb, int mult)
{
	int		n;
	char	c;

	if (nb < 0)
	{
		nb *= -1;
		write(1, "-", 1);
	}
	if (mult == 1)
	{
		c = '0' + nb;
		write(1, &c, 1);
		return (0);
	}
	else
	{
		n = (nb / mult);
		c = '0' + n;
		write(1, &c, 1);
		return (ft_putnbr_recursive(nb - ((nb / mult) * mult), mult / 10));
	}
}

int				get_mult(int32_t nb)
{
	int		i = 1;

	nb = (nb > 0) ? nb : nb * -1;
	while (nb / i >= 10)
		i *= 10;
	return (i);
}

static void		print_tiny_small(char* title, void* it, void* end)
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
			if (size != 0)
			{
				if (size > 0)
					total_size += size;
				putaddr((uint64_t)(it + sizeof(int32_t)));
				ft_putstr(" - ");
				putaddr((uint64_t)(it + sizeof(int32_t) + size));
				ft_putstr(" : ");
				ft_putnbr_recursive((size > 0) ? size : -1 * size, get_mult(size));
				ft_putstr(" octets ");
				ft_putendl((size > 0) ? "allocated" : "free");
			}
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
	void*		it;

	i = 0;
	max = (LARGE_PAGES_NB * getpagesize()) / sizeof(void*);
	ft_putendl("---------------------------------------------------------");
	ft_putendl("LARGE");
	while (i < max)
	{
		it = malloc_data_g.meta_large[i];
		if (it != NULL)
		{
			len = *(int32_t*)it;
			putaddr((uint64_t)(it + sizeof(int32_t)));
			ft_putstr(" - ");
			putaddr((uint64_t)(it + sizeof(int32_t) + len));
			ft_putstr(" : ");
			ft_putnbr_recursive(len, get_mult(len));
			ft_putendl(" octets");
		}
		++i;
	}
	ft_putendl("---------------------------------------------------------");
}

void			show_alloc_mem(void)
{
	if (malloc_data_g.datas[TINY] != NULL)
		print_tiny_small("TINY : ", malloc_data_g.datas[TINY], malloc_data_g.datas_end[TINY]);
	if (malloc_data_g.datas[SMALL] != NULL)
		print_tiny_small("SMALL : ", malloc_data_g.datas[SMALL], malloc_data_g.datas_end[SMALL]);
	if (malloc_data_g.meta_large != NULL)
		print_large();
}
