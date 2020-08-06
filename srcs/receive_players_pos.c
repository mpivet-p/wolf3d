/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_players_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:22:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/06 15:24:53 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

#include <stdio.h>

static void	new_player(t_core *wolf, char *buffer)
{
	t_vector	vec;

	(void)wolf;
	ft_memmove(&vec, buffer, sizeof(t_vector));
	printf("%f %f\n", vec.x, vec.y);
}

static void	if_packet(int socket, fd_set *rdfs)
{
	struct timeval	timeout;

	FD_ZERO(rdfs);
	FD_SET(socket, rdfs);
	timeout.tv_usec = 2000;
	timeout.tv_sec = 0;
	select(socket + 1, rdfs, NULL, NULL, &timeout);
}

int8_t	receive_players_pos(t_core *wolf)
{
	socklen_t	sinsize;
	char		buffer[SRV_BUFF];
	int			len;
	int			i;
	fd_set		rdfs;

	i = 0;
	sinsize = sizeof(struct sockaddr_in);
	while (i < 16)
	{
		if_packet(wolf->socket, &rdfs);
		if (!FD_ISSET(wolf->socket, &rdfs))
			return (SUCCESS);
		len = recvfrom(wolf->socket, buffer, SRV_BUFF, 0
				, (struct sockaddr*)&(wolf->sin), &sinsize);
		if (i == 0 && len == 1 && buffer[0] == SRV_TRS_START[0])
			continue ;
		if (len == 1 && buffer[0] == SRV_TRS_DONE[0])
			return (SUCCESS);
		if (len != sizeof(t_vector) || i >= MAX_PLAYERS)
			return (FAILURE);
		new_player(wolf, buffer);
		i++;
	}
	return (FAILURE);
}
