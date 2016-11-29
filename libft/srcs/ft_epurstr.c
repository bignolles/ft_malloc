/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 10:33:45 by marene            #+#    #+#             */
/*   Updated: 2015/05/07 10:51:27 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		epurlen(char *s)
{
	int		i;
	int		len;
	char	prev;

	i = 0;
	len = 0;
	prev = ' ';
	while (s[i])
	{
		if ((!ft_iswhite(prev) && ft_iswhite(s[i])) || !ft_iswhite(s[i]))
			++len;
		prev = s[i];
		++i;
	}
	return (len);
}

char			*ft_epurstr(char *s)
{
	int		i;
	int		j;
	int		epur_len;
	char	*epur;
	char	prev;

	i = 0;
	j = 0;
	epur_len = epurlen(s);
	if ((epur = malloc(sizeof(char) * (epur_len + 1))) != NULL)
	{
		epur[epur_len] = '\0';
		prev = ' ';
		while (j < epur_len)
		{
			if ((!ft_iswhite(prev) && ft_iswhite(s[i])) || !ft_iswhite(s[i]))
			{
				epur[j] = s[i];
				++j;
			}
			prev = s[i];
			++i;
		}
	}
	return (epur);
}
