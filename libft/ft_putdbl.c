/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 16:10:34 by evignol           #+#    #+#             */
/*   Updated: 2015/12/07 16:10:37 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/libft.h"

static void	init_stage_a(t_calc *tmp, double nb, int precision, char *flags)
{
	tmp->nb = nb;
	tmp->precision = precision;
	tmp->written = 0;
	if (tmp->nb < 0.0)
	{
		write(1, "-", 1);
		tmp->nb = -tmp->nb;
		tmp->written++;
	}
	else if (tmp->nb > 0.0 && flags[FLAG_PLUS])
		write(1, "+", 1);
	else if (tmp->nb > 0.0 && flags[FLAG_SPACE])
		write(1, " ", 1);
	else if (tmp->nb == 0.0)
	{
		write(1, "0", 1);
		tmp->written++;
	}
	ft_bzero(tmp->tmp, 320);
	tmp->old = tmp->nb;
	tmp->ent = (int)tmp->nb;
}

static void	init_stage_b(t_calc *tmp, char *flags)
{
	tmp->i = 0;
	while (tmp->nb >= 1.0)
	{
		tmp->tmp[319 - tmp->i] = ((unsigned long int)tmp->nb % 10) + '0';
		tmp->nb /= 10;
		tmp->i++;
	}
	tmp->written += tmp->i;
	tmp->j = tmp->i;
	while (tmp->j >= 0)
	{
		write(1, &tmp->tmp[319 - tmp->j], 1);
		tmp->j--;
	}
	if (tmp->precision > 0 || flags[FLAG_HASHTAG])
		write(1, ".", 1);
	tmp->nb = tmp->old - tmp->ent;
	tmp->i = 0;
	while (tmp->i != -tmp->precision)
	{
		tmp->i--;
		tmp->nb *= 10;
	}
}

int			ft_putdbl(double nb, int precision, char *flags)
{
	t_calc	tmp;

	init_stage_a(&tmp, nb, precision, flags);
	init_stage_b(&tmp, flags);
	tmp.i = 0;
	ft_bzero(tmp.tmp, 320);
	while (tmp.i < tmp.precision)
	{
		tmp.tmp[319 - tmp.i] = (unsigned long int)tmp.nb % 10 + '0';
		tmp.i++;
		tmp.nb /= 10;
	}
	tmp.j = tmp.i;
	tmp.i = 0;
	while (tmp.j >= 0 && tmp.i <= tmp.precision)
	{
		write(1, &tmp.tmp[319 - tmp.j], 1);
		tmp.j--;
		tmp.i++;
	}
	return (tmp.written + 1 + tmp.precision);
}
