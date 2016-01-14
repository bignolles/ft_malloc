/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char		**ft_create_tab(char const *s, char c)
{
	int		n;
	int		number_str;
	char	**tmp;

	n = 0;
	number_str = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		if (s[n] != '\0')
		{
			number_str++;
			while (s[n] != c && s[n] != '\0')
				n++;
		}
	}
	tmp = (char **)malloc(sizeof(char *) * (number_str + 1));
	tmp[number_str] = 0;
	return (tmp);
}

static char		*ft_create_str(char const *s, char c, int *n)
{
	int		n_bis;
	char	*str;
	int		index_str;

	index_str = 0;
	n_bis = *n;
	while (s[n_bis] != '\0' && s[n_bis] != c)
		n_bis++;
	str = (char *)malloc(sizeof(char) * (n_bis - *n + 1));
	while (*n < n_bis)
	{
		str[index_str] = s[*n];
		index_str++;
		*n = *n + 1;
	}
	str[index_str] = '\0';
	return (str);
}

static char		**ft_fill_tab(char const *s, char c, char **tmp)
{
	int		index_str_tab;
	int		n;

	index_str_tab = 0;
	n = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		if (s[n] != '\0')
		{
			tmp[index_str_tab] = ft_create_str(s, c, &n);
			index_str_tab++;
		}
	}
	return (tmp);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tmp;

	if (s != NULL)
	{
		tmp = ft_create_tab(s, c);
		tmp = ft_fill_tab(s, c, tmp);
		return (tmp);
	}
	return (0);
}
