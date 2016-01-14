/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:25:07 by evignol           #+#    #+#             */
/*   Updated: 2015/02/04 15:25:07 by evignol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/types.h>

static char	*ft_strkcat(char *dest, const char *src)
{
	unsigned int	i;
	unsigned int	j;
	char			*orig;

	orig = dest;
	i = 0;
	while (dest[i] != '\00')
		i++;
	j = 0;
	while (src[j] != '\n')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\00';
	return (orig);
}

static void	ft_rewind(char *str, char *pos)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = *(pos + i + 1);
		i++;
	}
}

static int	ft_get_next3(char **line, char *buff, int fd, int ret)
{
	char		tmp[BUFF_SIZE + 1];

	while (ret)
	{
		if (buff[0] == '\0')
		{
			ft_bzero(tmp, BUFF_SIZE + 1);
			ret = read(fd, tmp, BUFF_SIZE);
			ft_strcat(buff, tmp);
		}
		if (ret == 0 && buff[0] == '\0')
			return (0);
		*line = ft_realloc(*line, ft_strlen(*line) + BUFF_SIZE);
		if (ft_strchr(buff, '\n'))
		{
			ft_strkcat(*line, buff);
			ft_rewind(buff, ft_strchr(buff, '\n'));
			if (ft_strlen(buff) == 1 && buff[0] == '\n')
				ft_bzero(buff, BUFF_SIZE + 1);
			return (1);
		}
		ft_strcat(*line, buff);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	return (-1);
}

int			ft_get_next_line(int fd, char **line)
{
	static char	buff[BUFF_SIZE + 1] = {0};
	int			ret;

	ret = 1;
	if (*line == NULL)
		if ((*line = ft_memalloc(BUFF_SIZE + 1)) == NULL)
			return (-1);
	ret = ft_get_next3(line, buff, fd, ret);
	return (ret);
}
