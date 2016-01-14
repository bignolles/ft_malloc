/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:07 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:07 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

int		get_nb_digits(double nb)
{
	int		nb_digits;

	nb_digits = 0;
	while (nb > 1.0)
	{
		nb_digits++;
		nb /= 10.0;
	}
	return (nb_digits);
}

char	*get_integer_part(char *str, double nb, int nb_digits, int precision)
{
	int		i;

	i = 0;
	(void)precision;
	while (i < nb_digits)
	{
		str[nb_digits - 1 - i] = ((int)nb % 10) + '0';
		nb /= 10.0;
		i++;
	}
	return (str);
}

char	*get_decimal_part(char *str, double nb, int nb_digits, int precision)
{
	int		i;

	i = 0;
	while (i < precision)
	{
		nb *= 10.0;
		str[nb_digits - precision + 1 + i] = ((int)nb % 10) + '0';
		i++;
	}
	return (str);
}

char	*ft_ftostr(double nb, int precision)
{
	char	*str;
	int		nb_digits;

	nb_digits = get_nb_digits(nb) + precision;
	str = (char *)ft_memalloc(sizeof(char) * (nb_digits + precision + 1));
	if (!str)
		return (NULL);
	str = get_integer_part(str, nb, nb_digits - precision, 0);
	if (precision > 0)
	{
		str[nb_digits - precision] = '.';
		str = get_decimal_part(str, nb, nb_digits, precision);
	}
	return (str);
}
