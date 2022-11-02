/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:32:51 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/23 13:58:56 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_buf(int fd, char *buf)
{
	char	*tmp;
	int		i;

	if (!buf)
	{
		buf = malloc(1 * sizeof(char));
		buf[0] = 0;
	}
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (0);
	i = 1;
	while (i > 0 && ft_isnewline(buf) == 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i < 0)
		{
			free(tmp);
			return (0);
		}
		tmp[i] = 0;
		buf = ft_strjoin(buf, tmp);
	}
	free(tmp);
	return (buf);
}

char	*ft_get_line(char *buf)
{
	char		*line;
	size_t		i;

	if (buf[0] == 0)
		return (0);
	i = 1;
	while (buf[i - 1] != '\n' && buf[i])
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (buf[i] != '\n' && buf[i])
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = 0;
	}
	else
		line[i] = 0;
	return (line);
}

char	*ft_change_buf(char *buf)
{
	char	*newbuf;
	int		i;
	int		j;
	size_t	buf_len;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == 0)
	{
		free(buf);
		return (0);
	}
	buf_len = ft_strlen(buf);
	newbuf = malloc((buf_len - i + 1) * sizeof(char));
	i++;
	while (buf[i])
		newbuf[j++] = buf[i++];
	newbuf[j] = 0;
	free(buf);
	return (newbuf);
}

size_t	ft_isnewline(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*line;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buf = ft_get_buf(fd, buf);
	if (!buf)
		return (0);
	line = ft_get_line(buf);
	buf = ft_change_buf(buf);
	return (line);
}
