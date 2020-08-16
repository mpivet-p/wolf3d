/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:55:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/16 12:49:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "server.h"
#include "libft.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>

static int8_t	server_accept_connection(t_core *wolf)
{
	struct timeval	timeout;
	socklen_t		sinsize;
	fd_set			rdfs;
	char			buffer[16];

	timeout.tv_sec = 1;
	timeout.tv_usec = 100000;
	sinsize = sizeof(struct sockaddr);
	FD_ZERO(&rdfs);
	FD_SET(wolf->socket, &rdfs);
	select(wolf->socket + 1, &rdfs, NULL, NULL, &timeout);
	if (FD_ISSET(wolf->socket, &rdfs))
	{
		if (recvfrom(wolf->socket, buffer, 16, 0
			, (struct sockaddr*)&(wolf->sin), &sinsize) == 1 && buffer[0] == 6)
		{
			return (SUCCESS);
		}
	}
	close(wolf->socket);
	wolf->socket = -1;
	return (FAILURE);
}

int8_t			connect_to_server(t_core *wolf, const char *address)
{
	struct hostent		*hostinfo;

	if (init_socket(&(wolf->socket)) < 0)
		return (FAILURE);
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		ft_putstr_fd("wolf: Address error.\n", STDERR_FILENO);
		close(wolf->socket);
		return (FAILURE);
	}
	wolf->sin.sin_addr = *(struct in_addr*)hostinfo->h_addr;
	wolf->sin.sin_port = htons(WLF_PORT);
	wolf->sin.sin_family = PF_INET;
	ft_putstr_fd("wolf: Connecting to server...\n", STDERR_FILENO);
	send_pos_to_server(wolf);
	if (server_accept_connection(wolf) != SUCCESS)
	{
		ft_putstr_fd("wolf: server connection failure!\n", STDERR_FILENO);
		return (FAILURE);
	}
	ft_putstr_fd("wolf: connected!\n", STDERR_FILENO);
	return (SUCCESS);
}
