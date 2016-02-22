/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_recursive.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 18:43:49 by marene            #+#    #+#             */
/*   Updated: 2016/02/22 12:56:33 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

int				ft_putnbr_recursive(int32_t nb, int mult, int fd)
{
	int		n;
	char	c;

	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if (mult == 1)
	{
		c = '0' + nb;
		write(fd, &c, 1);
		return (0);
	}
	else
	{
		n = (nb / mult);
		c = '0' + n;
		write(fd, &c, 1);
		return (ft_putnbr_recursive(nb - ((nb / mult) * mult), mult / 10, fd));
	}
}

int				get_mult(int32_t nb)
{
	int		i;

	i = 1;
	nb = (nb > 0) ? nb : nb * -1;
	while (nb / i >= 10)
		i *= 10;
	return (i);
}
