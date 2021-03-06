/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 11:36:05 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/07 16:14:10 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <sys/socket.h>
#include <stdio.h>

/*
**	PF_INET = IPv4			PF_LOCAL = localhost
**	SOCK_STREAM => TCP		SOCK_DGRAM = UDP		SOCK_RAW = IP
*/

int8_t	init_socket(int *sockfd)
{
	*sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (*sockfd == INVALID_SOCKET)
	{
		ft_putstr_fd("wolf server: socket error\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}
