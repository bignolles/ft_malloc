/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	if (s != NULL)
	{
		new_str = (char *)malloc((sizeof(char) * len) + 1);
		i = 0;
		if (!new_str)
			return (NULL);
		while (i < len)
		{
			new_str[i] = s[start + i];
			i++;
		}
		new_str[i] = '\00';
		return (new_str);
	}
	return (NULL);
}
