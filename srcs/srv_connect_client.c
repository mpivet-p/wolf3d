/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_connect_client.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:00:23 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/16 14:00:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "server.h"
#include <stdio.h>
#include <sys/socket.h>

static void		print_addr(in_addr_t *addr, int port)
{
	ft_putnbr(*addr & 0x000000FF);
	write(STDOUT_FILENO, ".", 1);
	ft_putnbr((*addr & 0x0000FF00) >> 8);
	write(STDOUT_FILENO, ".", 1);
	ft_putnbr((*addr & 0x00FF0000) >> 16);
	write(STDOUT_FILENO, ".", 1);
	ft_putnbr((*addr & 0xFF000000) >> 24);
	write(STDOUT_FILENO, ":", 1);
	ft_putnbr(port);
}

static int8_t	connect_client(
		t_client *clients, struct sockaddr_in *csin, int *nbr, int socket)
{
	if (*nbr < MAX_CLIENTS)
	{
		clients[*nbr].sin = *csin;
		(*nbr)++;
		sendto(socket, "", 1, 0, (struct sockaddr*)csin
				, sizeof(struct sockaddr));
		ft_putstr("wolf server: New client connected: ");
		print_addr(&(csin->sin_addr.s_addr), csin->sin_port);
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	sendto(socket, "", 1, 0, (struct sockaddr*)csin, sizeof(struct sockaddr));
	ft_putstr_fd(
		"wolf server: Client tried to join. Server is full.\n", STDERR_FILENO);
	return (FAILURE);
}

int8_t			is_client_known(
		t_client *clients, struct sockaddr_in *csin, int *nbr, int socket)
{
	int	i;

	i = 0;
	while (i < *nbr)
	{
		if (csin->sin_addr.s_addr == clients[i].sin.sin_addr.s_addr
				&& csin->sin_port == clients[i].sin.sin_port)
			return (SUCCESS);
		i++;
	}
	return (connect_client(clients, csin, nbr, socket));
}
