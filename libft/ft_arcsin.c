/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arcsin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_arcsin(float x)
{
	float	res;
	float	x1;
	float	x2;
	float	x3;

	x1 = -0.2121144f * x;
	x2 = 0.0742610f * ft_pow(x, 2);
	x3 = -0.0187293f * ft_pow(x, 3);
	res = (PI / 2.f) - (ft_sqrt(1.f - x) * (1.5707288f + x1 + x2 + x3));
	return (res);
}