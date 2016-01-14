/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:12 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:12 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_getsize(char const *str)
{
	unsigned int	size;

	size = 0;
	while (str[size] != '\00')
	{
		size++;
	}
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_str;
	unsigned int	i;
	unsigned int	size_s1;
	unsigned int	size_s2;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size_s1 = ft_getsize(s1);
	size_s2 = ft_getsize(s2);
	new_str = (char *)malloc((sizeof(char) * (size_s1 + size_s2)) + 1);
	if (!new_str)
		return (NULL);
	while (i < (size_s1 + size_s2))
	{
		if (i < size_s1)
			new_str[i] = s1[i];
		new_str[size_s1 + i] = s2[i];
		i++;
	}
	new_str[size_s1 + i] = '\00';
	return (new_str);
}
