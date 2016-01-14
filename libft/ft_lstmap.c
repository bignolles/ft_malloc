/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:08 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:08 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp_new;
	t_list	*link;

	tmp = lst;
	new = NULL;
	while (tmp)
	{
		link = f(tmp);
		if (!link)
			return (NULL);
		if (!new)
		{
			new = link;
			tmp_new = new;
		}
		else
		{
			tmp_new->next = link;
			tmp_new = tmp_new->next;
		}
		tmp = tmp->next;
	}
	return (new);
}
