/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:10 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:10 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl(char const *s)
{
	unsigned int	size;

	size = 0;
	while (*((char *)s + size) != '\00')
		size++;
	write(1, s, size);
	write(1, "\n", 1);
}
