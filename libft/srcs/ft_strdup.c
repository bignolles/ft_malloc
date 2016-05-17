/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:48:00 by marene            #+#    #+#             */
/*   Updated: 2014/10/14 12:36:38 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*copy;

	i = 0;
	len = ft_strlen(s1) + 1;
	copy = malloc(len * sizeof(char));
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}
