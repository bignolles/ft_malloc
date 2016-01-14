/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:07 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:07 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		n;
	int		signe;

	i = 0;
	n = 0;
	signe = -1;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		signe = -signe;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		if (n != ((n * 10 - (str[i] - 48)) / 10))
			return (0);
		n = n * 10 - (str[i] - 48);
		i++;
	}
	return (n * signe);
}
