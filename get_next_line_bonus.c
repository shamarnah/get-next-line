/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samarnah <samarnah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:21:47 by samarnah          #+#    #+#             */
/*   Updated: 2025/10/02 17:47:59 by samarnah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*freebuf(char **buf)
{
	free(*buf);
	return (NULL);
}

static char	*readfromfile(char *buffer, int fd)
{
	char	*tmp;
	char	*buf;
	ssize_t	bytes;

	bytes = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (freebuf(&buffer));
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (freebuf(&buf));
		}
		buf[bytes] = '\0';
		tmp = buffer;
		buffer = ft_strjoin(tmp, buf);
		free(tmp);
		if (!buffer)
			return (freebuf(&buf));
	}
	free(buf);
	return (buffer);
}

static char	*bfrnewl(char *buffer)
{
	size_t	i;
	char	*line;

	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (freebuf(&buffer));
	ft_strlcpy(line, buffer, i + 1);
	return (line);
}

static char	*aftrnewl(char *buffer)
{
	size_t	i;
	char	*rest;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	rest = malloc(ft_strlen(buffer) - i + 1);
	if (!rest)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(rest, buffer + i, ft_strlen(buffer + i) + 1);
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	if (!ft_strchr(buffer[fd], '\n'))
		buffer[fd] = readfromfile(buffer[fd], fd);
	if (!buffer[fd] || *(buffer[fd]) == '\0')
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = bfrnewl(buffer[fd]);
	buffer[fd] = aftrnewl(buffer[fd]);
	return (line);
}
