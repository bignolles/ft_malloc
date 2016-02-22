/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 11:58:02 by marene            #+#    #+#             */
/*   Updated: 2016/02/22 14:46:28 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "ft_malloc.h"

extern t_metadata	g_malloc_data;

#ifdef RECORD_FILE_NAME

int					record_allocations_init(void)
{
	int			fd;
	static int	tmp = 0;

	if (tmp == 0)
	{
		fd = open(RECORD_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (fd != -1)
		{
			g_malloc_data.record_fd = fd;
			tmp = 1;
			return (M_OK);
		}
	}
	return (M_NOK);
}

#else

int					record_allocations_init(void)
{
	g_malloc_data.record_fd = -1;
	return (M_NOK);
}

#endif

void				record_allocations(char *title)
{
	if (g_malloc_data.record_fd != -1)
	{
		if (title != NULL)
		{
			ft_putendl_fd(title, g_malloc_data.record_fd);
		}
		display_allocs(g_malloc_data.record_fd);
		ft_putchar_fd('\n', g_malloc_data.record_fd);
	}
}
