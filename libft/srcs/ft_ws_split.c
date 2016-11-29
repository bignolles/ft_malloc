/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ws_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:17:18 by marene            #+#    #+#             */
/*   Updated: 2015/05/07 12:39:55 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static size_t	ft_wcount(const char *s)
{
	size_t	i;
	size_t	w_nb;

	i = 0;
	w_nb = 0;
	while (s[i])
	{
		if (!ft_iswhite(s[i]))
		{
			w_nb++;
			while (!ft_iswhite(s[i]))
			{
				if (!s[i])
					return (w_nb);
				i++;
			}
		}
		else
			i++;
	}
	return (w_nb);
}

static int		ft_word_len(const char *s, size_t i)
{
	size_t	w_len;

	w_len = 0;
	while (!ft_iswhite(s[i]))
	{
		if (!s[i])
			return (w_len);
		i++;
		w_len++;
	}
	return (w_len);
}

static char		**ft_makearray(const char *s)
{
	size_t		i;
	size_t		j;
	size_t		index;
	char		**array;
	size_t		len;

	index = 0;
	i = 0;
	len = ft_wcount(s);
	array = (char**)malloc(sizeof(char*) * (len + 1));
	array[len] = NULL;
	while (s[i] != '\0')
	{
		if (!ft_iswhite(s[i]))
		{
			j = ft_word_len(s, i);
			array[index] = ft_strsub(s, i, j);
			index++;
			i = i + j;
		}
		else
			i++;
	}
	return (array);
}

char			**ft_ws_split(char const *s)
{
	char	**array;

	if (ft_strcmp(s, "") == 0 || (ft_strlen(s) == 1 && ft_iswhite(s[0])))
	{
		array = malloc(sizeof(char*));
		array[0] = NULL;
		return (array);
	}
	else if (ft_strlen(s) == 1 && !ft_iswhite(s[0]))
	{
		array = malloc(sizeof(char*) * 2);
		ft_strcpy(array[0], "");
		array[1] = NULL;
	}
	array = ft_makearray(s);
	return (array);
}
