/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:59:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/23 01:57:03 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strnjoin(char *s1, char *s2, int len, char **line)
{
	char	*tmp;
	char	*str;

	if (!s2)
		return (NULL);
	tmp = ft_strsub(s2, 0, len);
	str = ft_strjoin(s1, tmp);
	ft_strdel(&tmp);
	ft_strdel(line);
	return (str);
}

static int		read_line(t_gnl *buffer, char **line, int i)
{
	while (++i <= buffer->ret && buffer->buf[i] != 10 && buffer->ret > 0)
	{
		if (buffer->buf[i] == 0 && buffer->ret == BUFF_SIZE)
		{
			*line = ft_strnjoin(*line, buffer->buf, i, line);
			ft_strclr(buffer->buf);
			if ((buffer->ret = read(buffer->fd, buffer->buf, BUFF_SIZE)) == -1)
				return (-1);
			buffer->buf[BUFF_SIZE] = 0;
			i = 0;
		}
	}
	if (ft_strchr(buffer->buf, '\n') || (buffer->buf[0] != 0 || *line[0] != 0))
		*line = ft_strnjoin(*line, buffer->buf, i++, line);
	if (ft_strchr(buffer->buf, '\n'))
		ft_strncpy(buffer->buf, ft_strchr(buffer->buf, '\n') + 1, BUFF_SIZE);
	else if (buffer->buf[0] != 0 || *line[0] != 0)
		ft_strclr(buffer->buf);
	else
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	buffer;
	int				ret;

	ret = -1;
	if (fd < 0 || line == NULL)
		return (-1);
	buffer.ret = BUFF_SIZE;
	buffer.fd = fd;
	*line = NULL;
	if (buffer.buf[0] == 0)
		buffer.ret = BUFF_SIZE;
	if ((ret = read_line(&buffer, &(*line), -1)) == 0)
		ft_strdel(line);
	return (ret);
}
