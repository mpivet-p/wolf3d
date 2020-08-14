/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_send_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:06:31 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/14 14:58:16 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <sys/socket.h>

static void	send_all_pos(t_client *client, int id, int client_nbr, int socket)
{
	int			i;
	socklen_t	sinsize;

	i = 0;
	sinsize = sizeof(struct sockaddr_in);
	sendto(socket, "", 1, 0
			, (struct sockaddr*)&(client[id].sin), sinsize);
	while (i < client_nbr)
	{
		if (i != id)
		{
			sendto(socket, &(client[i].player_pos), sizeof(t_vector), 0
					, (struct sockaddr*)&(client[id].sin), sinsize);
		}
		i++;
	}
	sendto(socket, "", 1, 0
			, (struct sockaddr*)&(client[id].sin), sinsize);
}

void		send_pos_to_clients(t_client *clients, int client_nbr, int socket)
{
	int			i;

	i = 0;
	while (i < client_nbr)
	{
		send_all_pos(clients, i, client_nbr, socket);
		i++;
	}
}
