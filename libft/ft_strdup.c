/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:12 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:12 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char			*new_buf;
	unsigned int	size;
	unsigned int	i;

	size = 0;
	i = 0;
	while (s[size] != '\00')
		size++;
	new_buf = (char *)malloc(sizeof(*new_buf) * (size + 1));
	if (!new_buf)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (i < size)
	{
		new_buf[i] = s[i];
		i++;
	}
	new_buf[i] = '\00';
	return (new_buf);
}
