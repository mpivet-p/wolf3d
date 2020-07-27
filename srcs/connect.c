/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:55:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/27 15:41:52 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "server.h"
#include "libft.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>

int8_t	connect_to_server(const char *address)
{
	struct sockaddr_in	sin;
	struct hostent		*hostinfo;
	int					socket;

	if (init_socket(&socket) < 0)
		return (FAILURE);
	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		ft_putstr_fd("wolf: Address error.\n", STDERR_FILENO);
		close(socket);
		return (FAILURE);
	}
	sin.sin_addr = *(struct in_addr*)hostinfo->h_addr;
	sin.sin_port = htons(WLF_PORT);
	sin.sin_family = PF_INET;
	if (sendto(socket, "", 0, 0, (struct sockaddr*)&sin, sizeof(sin)) < 0)
		dprintf(STDERR_FILENO, "ERROR\n");
	close(socket);
	return (socket);
}
