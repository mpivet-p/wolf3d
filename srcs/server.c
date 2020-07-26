/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:16:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/26 12:50:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <sys/socket.h>

int8_t	init_socket(int *sockfd)
{
	/*
	**	PF_INET = IPv4			PF_LOCAL = localhost
	**	SOCK_STREAM => TCP		SOCK_DGRAM = UDP		SOCK_RAW = IP
	*/
	*sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (*sockfd == INVALID_SOCKET)
	{
		ft_putstr_fd("wolf server: socket error\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	create_interface(int sockfd)
{
	struct sockaddr_in	sin;

	ft_bzero(&sin, sizeof(sin));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = PF_INET;
	sin.sin_port = htons(WLF_PORT);
	if (bind(sockfd, (struct sockaddr*) &sin, sizeof(sin)) == SOCKET_ERROR)
	{
		ft_putstr_fd("wolf server: bind failure\n", STDERR_FILENO);
		close(sockfd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	receive(int socket, char *buffer, struct sockaddr_in *csin, int *len)
{
	size_t	sinsize;

	sinsize = sizeof(*csin);
	if ((*len = recvfrom(socket, buffer, SRV_BUFF
					, 0, (struct sockaddr*)csin, (socklen_t*)&sinsize)) < 0)
	{
		ft_putstr_fd("wolf server: recvfrom error\n", STDERR_FILENO);
		return (FAILURE);
	}
	buffer[*len] = 0;
	return (SUCCESS);
}

static int8_t	connect_client(t_client *clients, struct sockaddr_in *csin, int *nbr)
{
	if (*nbr < MAX_CLIENTS)
	{
		clients[*nbr].addr = csin->sin_addr.s_addr;
		(*nbr)++;
		return (SUCCESS);
	}
	ft_putstr_fd("wolf server: Server is full !\n", STDERR_FILENO);
	return (FAILURE);
}

static int8_t	is_client_known(t_client *clients, struct sockaddr_in *csin, int *nbr)
{
	int	i;

	i = 0;
	while (i < *nbr)
	{
		if (csin->sin_addr.s_addr == clients[i].addr)
			return (SUCCESS);
		i++;
	}
	return (connect_client(clients, csin, nbr));
}

static void	remove_client(t_client *clients, in_addr_t address, int *nbr)
{
	int	id;

	id = 0;
	while (id < *nbr || clients[id].addr != address)
		id++;
	if (id < *nbr)
		ft_memmove(clients + id, clients + id + 1
				, sizeof(t_client) * (MAX_CLIENTS - *nbr + id));
}

static int8_t	process_data(char *buffer, int len)
{
	if (buffer[0] == 4)
		return (FAILURE);
	(void)len;
	ft_putstr("wolf server: New data received\n");
	return (SUCCESS);
}

static void	run_server(int socket, t_client *clients)
{
	struct sockaddr_in	csin;
	int					client_nbr;
	fd_set				rdfs;
	char				buffer[SRV_BUFF + 1];
	int					len;

	while(1)
	{
		FD_ZERO(&rdfs);
		FD_SET(socket, &rdfs);
		if(select(socket + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			;
			//close_all_connections();
		}
		if (FD_ISSET(socket, &rdfs))
		{
			ft_bzero(&csin, sizeof(csin));
			receive(socket, buffer, &csin, &len);
			if (is_client_known(clients, &csin, &client_nbr) == SUCCESS)
				if (process_data(buffer, len) != SUCCESS)
					remove_client(clients, csin.sin_addr.s_addr, &client_nbr);
		}
	}
}

int		main(void)
{
	t_client	clients[MAX_CLIENTS];
	int			socket;

	if (init_socket(&socket) != SUCCESS)
		return (EXIT_FAILURE);
	if (create_interface(socket) != SUCCESS)
		return (EXIT_FAILURE);
	run_server(socket, clients);
	close(socket);
	return (EXIT_SUCCESS);
}
