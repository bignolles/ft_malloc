/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:07 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:07 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <libft.h>

void	ft_fputhexa(uint64_t n, char size)
{
	char	sym[16];
	char	*res;
	int		i;

	ft_strcpy(sym, "0123456789abcdef");
	res = ft_memalloc(sizeof(char) * (size + 1));
	if (!res)
		return ;
	ft_memset(res, '0', size);
	i = size - 1;
	while (n > 0)
	{
		res[i] = sym[n % 16];
		n = n - (n % 16);
		n /= 16;
		i--;
	}
	write(1, res, size);
}
