/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_players_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:22:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/13 15:12:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"

#include <stdio.h>

static void	new_player(t_core *wolf, char *buffer)
{
	t_vector	vec;

	ft_memmove(&(vec), buffer, sizeof(t_vector));
	wolf->world.player_nbr++;
	wolf->world.sprites[wolf->world.sprt_nbr].x = vec.x;
	wolf->world.sprites[wolf->world.sprt_nbr].y = vec.y;
	//CHANGE TO wolf->world.player_tex; NEED PARSING
	wolf->world.sprites[wolf->world.sprt_nbr].tex_id = TEX_MAX;
	wolf->world.sprt_nbr++;
}

static void	if_packet(int socket, fd_set *rdfs)
{
	struct timeval	timeout;

	FD_ZERO(rdfs);
	FD_SET(socket, rdfs);
	timeout.tv_usec = 20;
	timeout.tv_sec = 0;
	select(socket + 1, rdfs, NULL, NULL, &timeout);
}

void	erase_players_sprites(t_core *wolf)
{
	wolf->world.sprt_nbr -= wolf->world.player_nbr;
	ft_bzero(&(wolf->world.sprites[wolf->world.sprt_nbr])
			, (SPRT_MAX - wolf->world.sprt_nbr) * sizeof(t_sprite));
	wolf->world.player_nbr = 0;
}

static int8_t	receive_treat_data(t_core *wolf, char *buffer, int *i, socklen_t *sinsize)
{
	int			len;

	len = recvfrom(wolf->socket, buffer, SRV_BUFF, 0
			, (struct sockaddr*)&(wolf->sin), sinsize);
	if (*i == 0 && len == 1 && buffer[0] == SRV_TRS_START[0])
	{
		erase_players_sprites(wolf);
		return (SUCCESS);
	}
	if (len == 1 && buffer[0] == SRV_TRS_DONE[0])
	{
		*i = 16;
		return (SUCCESS);
	}
	if (len != sizeof(t_vector) || *i >= MAX_PLAYERS)
		return (FAILURE);
	(*i)++;
	new_player(wolf, buffer);
	return (SUCCESS);
}

int8_t		receive_players_pos(t_core *wolf)
{
	socklen_t	sinsize;
	char		buffer[SRV_BUFF];
	int			i;
	fd_set		rdfs;

	i = 0;
	sinsize = sizeof(struct sockaddr);
	while (i < 16)
	{
		if_packet(wolf->socket, &rdfs);
		if (!FD_ISSET(wolf->socket, &rdfs))
			return (SUCCESS);
		if (receive_treat_data(wolf, buffer, &i, &sinsize) == FAILURE)
			return (FAILURE);
	}
	return (FAILURE);
}
