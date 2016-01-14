/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:10 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:10 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void	ft_putnbr_long(unsigned long long n)
{
	char	*nbr;
	size_t	i;

	i = 0;
	nbr = ft_itoa(n);
	while (nbr[i] == '-' || (nbr[i] >= 48 && nbr[i] <= 57))
		i++;
	write(1, nbr, i);
}
