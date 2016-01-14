/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:10 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:10 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void		ft_puthex(unsigned long val)
{
	char	c;

	if (val >= 16)
	{
		ft_puthex(val / 16);
		ft_puthex(val % 16);
	}
	else if (val > 9)
	{
		c = val + 'a' - 10;
		write(1, &c, 1);
	}
	else if (val <= 9)
	{
		c = val + '0';
		write(1, &c, 1);
	}
}
