/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		get_dec_pos(char *str)
{
	int		pos;

	pos = 0;
	while (str[pos] != '\0' && str[pos] != '.')
		pos++;
	return (pos);
}

static float	calc_mult(char *str)
{
	float	mult;
	int		i;

	mult = 1.0f;
	i = get_dec_pos(str) + 1;
	while (str[i] != '\0')
	{
		mult /= 10.0f;
		i++;
	}
	return (mult);
}

float			ft_atof(char *str)
{
	float	nbr;
	float	mult;
	int		i;

	nbr = 0.0f;
	i = ft_strlen(str) - 1;
	mult = calc_mult(str);
	while (i >= 0)
	{
		if (str[i] != '.' && str[i] != '-')
		{
			nbr += (str[i] - '0') * mult;
			mult *= 10;
		}
		i--;
	}
	if (str[0] == '-')
		nbr = -nbr;
	return (nbr);
}
