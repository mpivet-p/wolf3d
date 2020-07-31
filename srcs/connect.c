/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:55:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/31 15:02:14 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "server.h"
#include "libft.h"
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>

int8_t	connect_to_server(t_core *wolf, const char *address)
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
	return (send_pos_to_server(wolf));
}
