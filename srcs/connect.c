/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 14:55:04 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/23 15:53:24 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int8_t	connect_to_server(const char *address)
{
	struct sockaddr_in	sin;
	struct hostent		*hostinfo;

	hostinfo = gethostbyname(address);
	if (hostinfo == NULL)
	{
		ft_putstr_fd("wolf: Address error.\n", STDERR_FILENO);
		return (FAILURE);
	}
	sin.sin_addr = *(struct in_addr*)hostinfo->h_addr;
	sin.port = htons(WOLF_PORT);
	sin.sin_family = PF_INET;
	connect(
	return (socket);
}
