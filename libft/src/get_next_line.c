/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 06:08:28 by bcozic            #+#    #+#             */
/*   Updated: 2018/01/23 02:26:29 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static int	test_end(char *save, char *buff)
{
	int		i;
	size_t	size;

	i = 0;
	while (buff[i])
	{
		if (buff[i++] == '\n')
		{
			size = ft_strlen(buff + i);
			ft_memmove(buff, buff + i, size);
			buff[size] = '\0';
			break ;
		}
	}
	i = -1;
	while (save[++i])
	{
		if (save[i] == '\n')
		{
			save[i] = '\0';
			return (1);
		}
	}
	return (2);
}

static int	read_line(const int fd, char *buff)
{
	int		c;

	if (BUFF_SIZE <= 0)
		return (-1);
	c = (int)read(fd, buff, BUFF_SIZE);
	buff[c] = '\0';
	return (c);
}

int			get_next_line(const int fd, char **line)
{
	static char	buff[BUFF_SIZE + 1] = "";
	char		*str;
	int			end;
	int			c;

	str = NULL;
	if (!line)
		return (-1);
	end = 2;
	if (!(*line = ft_strjoinflush(&str, buff)))
		return (-1);
	end = test_end(*line, buff);
	while (end == 2)
	{
		if ((c = read_line(fd, buff)) <= 0)
		{
			if (*line[0])
				return (1);
			return (c);
		}
		if (!(ft_strjoinflush(line, buff)))
			return (-1);
		end = test_end(*line, buff);
	}
	return (1);
}
