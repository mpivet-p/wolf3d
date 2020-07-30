/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_pos_to_server.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:54:00 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/30 14:56:08 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <sys/socket.h>
#include <stdio.h>

int8_t	send_pos_to_server(t_core *wolf)
{
	if (sendto(wolf->socket, &(wolf->cam.pos), sizeof(t_vector), 0
		, (struct sockaddr*)&(wolf->sin), sizeof(struct sockaddr_in)) < 0)
	{
		ft_putstr_fd("wolf: player position couldn't been send to server\n"
				, STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}
