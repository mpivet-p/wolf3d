/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_players_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:22:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/05 17:50:59 by mpivet-p         ###   ########.fr       */
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

int8_t	receive_players_pos(t_core *wolf)
{
	socklen_t	sinsize;
	char		buffer[SRV_BUFF];
	int			len;
	int			i;

	i = 0;
	sinsize = sizeof(struct sockaddr_in);
	printf("before loop\n");
	while (i < 16)
	{
		ft_bzero(buffer, SRV_BUFF);
		printf("before read\n");
		len = recvfrom(wolf->socket, buffer, SRV_BUFF, 0
				, (struct sockaddr*)&(wolf->sin), &sinsize);
		printf("after read\n");
		if (i == 0 && len == 1 && ft_strcmp(buffer, SRV_TRS_START))
			continue ;
		if (len >= 1 && ft_strcmp(SRV_TRS_DONE, buffer))
			return (SUCCESS);
		if (len != sizeof(t_vector) || i >= MAX_PLAYERS)
			return (FAILURE);
		new_player(wolf, buffer);
		i++;
	}
	return (FAILURE);
}
