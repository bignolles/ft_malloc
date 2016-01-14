/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:12 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:12 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	size_s;
	char	*new_str;

	i = 0;
	size_s = 0;
	if (s != NULL && f != NULL)
	{
		while (s[size_s] != '\00')
		{
			size_s++;
		}
		new_str = (char *)malloc(sizeof(char) * size_s);
		if (!new_str)
		{
			return (NULL);
		}
		while (s[i] != '\00')
		{
			new_str[i] = f(s[i]);
			i++;
		}
		return (new_str);
	}
	return (NULL);
}
