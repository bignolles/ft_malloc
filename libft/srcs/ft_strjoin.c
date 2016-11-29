/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/06 16:46:43 by marene            #+#    #+#             */
/*   Updated: 2014/11/01 14:45:54 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static char		*ft_make_join(size_t len1, size_t len2, char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	join = ft_strnew(len1 + len2 + 1);
	join[len1 + len2] = '\0';
	while (i < len1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < len2 + len1)
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	return (join);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;

	len1 = (s1 != NULL) ? ft_strlen(s1) : 0;
	len2 = (s2 != NULL) ? ft_strlen(s2) : 0;
	join = ft_make_join(len1, len2, (char*)s1, (char*)s2);
	return (join);
}
