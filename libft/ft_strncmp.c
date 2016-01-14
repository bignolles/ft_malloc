/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:13 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:13 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n == 1 && *s1 == *s2)
		return (0);
	while (s1[i] != '\00' && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	if (s1[i] < s2[i])
		return (1);
	else if (s1[i] > s2[i])
		return (-1);
	else
		return (0);
	return (s1[i] - s2[i]);
}
