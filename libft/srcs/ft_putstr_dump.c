/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_dump.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 18:48:04 by marene            #+#    #+#             */
/*   Updated: 2016/02/22 18:50:46 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstr_dump(char *str, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (ft_isprint(str[i]))
			ft_putchar(str[i]);
		else
			ft_putchar('.');
		++i;
	}
	ft_putchar('\n');
}
