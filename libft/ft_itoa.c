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

int		ft_count_char(int n)
{
	int		nb_char;

	nb_char = 0;
	if (n == 0)
		nb_char++;
	else
	{
		if (n < 0)
			nb_char++;
		while (((n / 10) != 0) || ((n % 10) != 0))
		{
			nb_char++;
			n = n / 10;
		}
	}
	return (nb_char);
}

char	*ft_itoa(int n)
{
	int		nb_char;
	char	*str;

	nb_char = ft_count_char(n);
	str = (char *)malloc(sizeof(char) * (nb_char + 1));
	str[nb_char] = '\0';
	if (n == -2147483648)
		ft_strcpy(str, "-2147483648");
	else if (n == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
		{
			str[0] = '-';
			n = n * -1;
		}
		while (n > 0)
		{
			str[nb_char - 1] = (char)((n % 10) + '0');
			nb_char--;
			n /= 10;
		}
	}
	return (str);
}
