/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:43:53 by marene            #+#    #+#             */
/*   Updated: 2016/02/01 17:16:14 by marene           ###   ########.fr       */
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

void			show_alloc_mem(void)
{
	void*		it;
	int32_t		size;
	int32_t		total_size;

	total_size = 0;
	it = malloc_data_g.datas[TINY];
	ft_putendl("---------------------------------------------------------");
	ft_putstr("TINY : ");
	putaddr((unsigned long int)it);
	ft_putstr(" - ");
	putaddr((unsigned long int)malloc_data_g.datas_end[TINY]);
	ft_putstr(" [MAX ALLOC : ");
	ft_putnbr_recursive(alloc_maxsize_g, get_mult(alloc_maxsize_g));
	ft_putstr(" bytes]");
	ft_putchar('\n');
	while (it < malloc_data_g.datas_end[TINY] - sizeof(int32_t))
	{
		size = 0;
		if (it != NULL)
		{
			size = *(int32_t*)it;
			if (size > 0)
			{
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
	ft_putstr("TINY : ");
	putaddr((unsigned long int)it);
	ft_putstr(" - ");
	putaddr((unsigned long int)malloc_data_g.datas_end[TINY]);
	ft_putstr(" [MAX ALLOC : ");
	ft_putnbr_recursive(alloc_maxsize_g, get_mult(alloc_maxsize_g));
	ft_putstr(" bytes]");
	ft_putchar('\n');
	ft_putstr("total size : ");
	ft_putnbr_recursive(total_size, get_mult(total_size));
	ft_putendl(" octets");
	ft_putendl("---------------------------------------------------------");
}
