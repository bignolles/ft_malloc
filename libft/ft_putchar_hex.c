/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 11:24:17 by marene            #+#    #+#             */
/*   Updated: 2016/02/19 13:19:29 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void		ft_putchar_hex(unsigned char *p)
{
	static char		base16[] = "0123456789abcdef";
	char			res[2];
	int				i;
	unsigned char	c;

	c = *p;
	i = 1;
	res[0] = '0';
	res[1] = '0';
	while (c > 0)
	{
		res[i] = base16[c % 16];
		c = c - (c % 16);
		c /= 16;
		--i;
	}
	write(1, res, 2);
}

void		ft_putint_hex(unsigned int *p)
{
	static char		base16[] = "0123456789abcdef";
	char			res[8];
	int				i;
	unsigned int	c;

	c = *p;
	i = 7;
	ft_memset(res, '0', 8);
	while (c > 0)
	{
		res[i] = base16[c % 16];
		c = c - (c % 16);
		c /= 16;
		--i;
	}
	i = 0;
	while (i < 8)
	{
		ft_putchar(res[i]);
		if (i > 0 && i % 2 != 0)
			ft_putchar(' ');
		++i;
	}
}
