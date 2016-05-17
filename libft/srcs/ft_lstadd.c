/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 11:08:56 by marene            #+#    #+#             */
/*   Updated: 2014/10/14 12:35:09 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new && alst && *alst)
	{
		new->next = *alst;
		*alst = new;
	}
}
