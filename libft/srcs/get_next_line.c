/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/04 17:46:35 by marene            #+#    #+#             */
/*   Updated: 2014/10/14 17:30:33 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

/*
** In order to avoid memory leaks, you should make sure to free(3) the string
** pointed to by get_next_line's 2nd parameter (char **line).
** This put aside, get_next_line does not generates any memory leaks: If some
** appears, you're not using it the right way!
*/

static void		ft_get_line(char **line, char *buffer, size_t *position)
{
	*position = ft_strchr(buffer, '\n') - buffer;
	*line = ft_strsub(buffer, 0, *position);
}

static void		ft_buffer_trim(char **buffer, size_t position)
{
	char	*save;

	save = *buffer;
	*buffer = ft_strsub(save, position + 1, ft_strlen(save) - position - 1);
	free(save);
}

int				ft_return(int ret, char **buff2, char **line, size_t *position)
{
	if (ret == 0 && ft_strchr(*buff2, '\n') == NULL)
	{
		*line = ft_strdup(*buff2);
		return (0);
	}
	ft_get_line(line, *buff2, position);
	ft_buffer_trim(buff2, *position);
	return (1);
}

int				get_next_line(int const fd, char **line, int flag)
{
	char				r_buff[BUFF_SIZE + 1];
	int					ret;
	static char			*s_buff = NULL;
	size_t				position;
	char				*save;

	if (fd < 0 || BUFF_SIZE < 0 || !line || (!s_buff
			&& (s_buff = ft_strnew(BUFF_SIZE + 1)) == NULL))
		return (-1);
	if (flag == FLUSH)
	{
		*line = ft_strdup(s_buff);
		return (0);
	}
	while (s_buff && ft_strchr(s_buff, (int)'\n') == NULL
			&& (ret = read(fd, r_buff, BUFF_SIZE)) > 0)
	{
		save = s_buff;
		r_buff[ret] = '\0';
		s_buff = ft_strjoin(s_buff, r_buff);
		free(save);
	}
	return (ft_return(ret, &s_buff, line, &position));
}
