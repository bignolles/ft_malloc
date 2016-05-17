/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 15:20:11 by marene            #+#    #+#             */
/*   Updated: 2014/10/14 12:41:05 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	str = NULL;
	i = 0;
	if (size > 0)
	{
		str = (char*)malloc(sizeof(char) * size);
		if (str != NULL)
		{
			while (i < size)
			{
				str[i] = '\0';
				i++;
			}
		}
	}
	return (str);
}
