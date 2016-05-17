/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 10:17:13 by marene            #+#    #+#             */
/*   Updated: 2016/04/29 14:25:55 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*str;

	len = ft_strlen(s);
	start = 0;
	end = len - 1;
	while (s[start] && ft_strchr(BLANK_CHARS, s[start]) != NULL)
		start++;
	while (end > 0 && ft_strchr(BLANK_CHARS, s[end]) != NULL)
		end--;
	str = (end > start) ? ft_strsub(s, start, end - start + 1) : NULL;
	if (str != NULL)
		str[end - start + 1] = '\0';
	return (str);
}
