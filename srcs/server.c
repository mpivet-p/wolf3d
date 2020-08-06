/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:16:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/06 15:43:49 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <sys/socket.h>

#include <stdio.h>

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

static void	print_addr(in_addr_t	*addr, int port)
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

static int8_t	connect_client(t_client *clients, struct sockaddr_in *csin, int *nbr)
{
	if (*nbr < MAX_CLIENTS)
	{
		clients[*nbr].sin = *csin;
		(*nbr)++;
		ft_putstr("wolf server: New client connected: ");
		printf("new port : %d\n", csin->sin_port);
		print_addr(&(csin->sin_addr.s_addr), csin->sin_port);
		write(STDOUT_FILENO, "\n", 1);
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
		if (csin->sin_addr.s_addr == clients[i].sin.sin_addr.s_addr
				&& csin->sin_port == clients[i].sin.sin_port)
			return (SUCCESS);
		i++;
	}
	return (connect_client(clients, csin, nbr));
}

static void	remove_client(t_client *clients, in_addr_t address, int *nbr)
{
	int	id;

	id = 0;
	ft_putstr("wolf server: Client disconnected\n");
	while (id < *nbr && clients[id].sin.sin_addr.s_addr != address)
		id++;
	if (id < *nbr)
	{
		ft_memmove(&(clients[id]), &(clients[id + 1])
				, sizeof(t_client) * (MAX_CLIENTS - id));
		(*nbr)--;
	}
}

static void		send_all_pos(t_client *client, struct sockaddr_in *sin, int id, int client_nbr, int socket)
{
	int		i;

	i = 0;
	sendto(socket, "", 1, 0
			, (struct sockaddr*)&(client[id].sin), sizeof(struct sockaddr_in));
	while (i < client_nbr)
	{
		if (i != id)
		{
			printf("Sending %d data to %d (%f %f)\n", sin->sin_port, client[id].sin.sin_port, client[id].player_pos.x, client[id].player_pos.y);
			sendto(socket, &(client[i].player_pos), sizeof(t_vector), 0
					, (struct sockaddr*)&(client[id].sin), sizeof(struct sockaddr_in));
		}
		i++;
	}
	sendto(socket, "", 1, 0
			, (struct sockaddr*)&(client[id].sin), sizeof(struct sockaddr_in));
}

static void		send_pos_to_clients(t_client *clients
		, struct sockaddr_in *sin, int client_nbr, int socket)
{
	int			i;

	i = 0;
	while (i < client_nbr)
	{
		if (sin->sin_port != clients[i].sin.sin_port)
			send_all_pos(clients, sin, i, client_nbr, socket);
		i++;
	}
}

static void	set_player_pos(t_client *clients, char *buffer, struct sockaddr_in *sin)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS && sin->sin_port != clients[i].sin.sin_port)
		i++;
	ft_memmove(&(clients[i].player_pos), buffer, sizeof(t_vector));
}

static void	run_server(int socket, t_client *clients)
{
	struct sockaddr_in	csin;
	int					client_nbr;
	fd_set				rdfs;
	char				buffer[SRV_BUFF + 1];
	int					len;

	while (1)
	{
		FD_ZERO(&rdfs);
		FD_SET(STDIN_FILENO, &rdfs);
		FD_SET(socket, &rdfs);
		select(socket + 1, &rdfs, NULL, NULL, NULL);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			close(socket);
			ft_putstr_fd("wolf server: Server closing...\n", STDOUT_FILENO);
			return ;
		}
		if (FD_ISSET(socket, &rdfs))
		{
			ft_bzero(&csin, sizeof(csin));
			receive(socket, buffer, &csin, &len);
			if (is_client_known(clients, &csin, &client_nbr) == SUCCESS)
			{
				if (len != sizeof(t_vector))
					remove_client(clients, csin.sin_addr.s_addr, &client_nbr);
				else
				{
					set_player_pos(clients, buffer, &csin);
					send_pos_to_clients(clients, &csin, client_nbr, socket);
				}
			}	
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
	ft_putstr_fd("wolf server: Server is running...\n", STDERR_FILENO);
	run_server(socket, clients);
	close(socket);
	return (EXIT_SUCCESS);
}
