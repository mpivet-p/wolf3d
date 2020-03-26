/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 01:43:52 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/06/16 01:43:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		how_many_lines(const int fd)
{
	char	*line;
	int		c;

	line = NULL;
	c = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		c++;
	}
	return (c);
}
