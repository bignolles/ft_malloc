/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:08 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:08 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*data;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	ft_bzero((void *)new, sizeof(*new));
	if (content)
	{
		data = (void *)malloc(content_size);
		if (!data)
			return (NULL);
		ft_bzero(data, content_size);
		new->content = data;
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}
