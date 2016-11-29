/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/14 12:33:45 by marene            #+#    #+#             */
/*   Updated: 2014/10/29 14:26:27 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_error.h>

int		tryint(int err, int res, char *error)
{
	if (res == err)
	{
		ft_putstr("Error: ");
		ft_putendl(error);
		exit(EXIT_FAILURE);
	}
	return (res);
}

void	*tryptr(void *err, void *res, char *error)
{
	if (res == err)
	{
		ft_putstr("Error: ");
		ft_putendl(error);
		exit(EXIT_FAILURE);
	}
	return (res);
}
