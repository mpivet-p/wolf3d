/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_connect_client.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:00:23 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/12 11:23:39 by mpivet-p         ###   ########.fr       */
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
		t_client *clients, struct sockaddr_in *csin, int *nbr)
{
	if (*nbr < MAX_CLIENTS)
	{
		clients[*nbr].sin = *csin;
		(*nbr)++;
		ft_putstr("wolf server: New client connected: ");
		print_addr(&(csin->sin_addr.s_addr), csin->sin_port);
		write(STDOUT_FILENO, "\n", 1);
		return (SUCCESS);
	}
	ft_putstr_fd("wolf server: Server is full !\n", STDERR_FILENO);
	return (FAILURE);
}

int8_t			is_client_known(
		t_client *clients, struct sockaddr_in *csin, int *nbr)
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
	return (connect_client(clients, csin, nbr));
}
