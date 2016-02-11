/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 18:37:04 by marene            #+#    #+#             */
/*   Updated: 2016/02/11 18:38:46 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void			putaddr(unsigned long int n)
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
