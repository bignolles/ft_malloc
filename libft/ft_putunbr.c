/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:10 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:10 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:08 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:08 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_char(unsigned int n)
{
	int		nb_char;

	nb_char = 0;
	if (n == 0)
		nb_char++;
	else
	{
		while (((n / 10) != 0) || ((n % 10) != 0))
		{
			nb_char++;
			n = n / 10;
		}
	}
	return (nb_char);
}

static char	*ft_uitoa(unsigned int n)
{
	int		nb_char;
	char	*str;

	nb_char = ft_count_char(n);
	str = (char *)malloc(sizeof(char) * (nb_char + 1));
	str[nb_char] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		while (n > 0)
		{
			str[nb_char - 1] = (char)((n % 10) + '0');
			nb_char--;
			n /= 10;
		}
	}
	return (str);
}


void		ft_putunbr(unsigned int n)
{
	char	*nbr;
	size_t	i;

	i = 0;
	nbr = ft_uitoa(n);
	while (nbr[i] >= 48 && nbr[i] <= 57)
		i++;
	write(1, nbr, i);
	free(nbr);
}
