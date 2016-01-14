/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arctan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:06 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:06 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static float	ftabs(float val)
{
	if (val < 0)
		return (-val);
	return (val);
}

float			ft_arctan(float x)
{
	float	a;

	a = (PI / 4) * x;
	return (a - (x * (ftabs(x) - 1.f)) * ((0.2447f + 0.0663f) * ftabs(x)));
}
