/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:11 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:11 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_strclr(char *s)
{
	unsigned int	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\00')
		{
			s[i] = '\00';
			i++;
		}
	}
}