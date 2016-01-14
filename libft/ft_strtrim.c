/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_lenofstr(char const *str)
{
	int		i;

	i = 0;
	while (str[i] != '\00')
	{
		i++;
	}
	i--;
	return (i);
}

char	*ft_strtrim(char const *s)
{
	char	*new_str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (s != NULL)
	{
		k = ft_lenofstr(s);
		while (k > 0 && (s[k] == ' ' || s[k] == '\n' || s[k] == '\t'))
			k--;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		if (i > k)
			i = 1;
		new_str = (char *)malloc(sizeof(char) * ((k + 1) - (i - 1)));
		if (!new_str)
			return (NULL);
		while (i <= k)
			new_str[j++] = s[i++];
		new_str[j] = '\00';
		return (new_str);
	}
	return (NULL);
}
