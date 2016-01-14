/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:10 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:10 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	unsigned int	size;

	size = 0;
	while (s[size] != '\00')
		size++;
	write(fd, s, size);
	write(fd, "\n", 1);
}
