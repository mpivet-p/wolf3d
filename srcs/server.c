/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:16:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/15 15:58:34 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "libft.h"
#include <sys/socket.h>
#include <stdio.h>

int8_t		create_interface(int sockfd)
{
	struct sockaddr_in	sin;

	ft_bzero(&sin, sizeof(sin));
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = PF_INET;
	sin.sin_port = htons(WLF_PORT);
	if (bind(sockfd, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		ft_putstr_fd("wolf server: bind failure\n", STDERR_FILENO);
		close(sockfd);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	set_player_pos(t_client *clients, char *buffer
		, struct sockaddr_in *sin)
{
	int	i;

	i = 0;
	while (i < MAX_CLIENTS && sin->sin_port != clients[i].sin.sin_port)
		i++;
	ft_memmove(&(clients[i].player_pos), buffer, sizeof(t_vector));
}

static void	wait_event(int socket, fd_set *rdfs)
{
	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(socket, rdfs);
	select(socket + 1, rdfs, NULL, NULL, NULL);
}

static void	run_server(int socket, t_client *clients)
{
	struct sockaddr_in	csin;
	fd_set				rdfs;
	char				buffer[SRV_BUFF + 1];
	int					client_nbr;
	int					len;

	while (1)
	{
		wait_event(socket, &rdfs);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
			break ;
		if (FD_ISSET(socket, &rdfs))
		{
			receive(socket, buffer, &csin, &len);
			if (is_client_known(clients, &csin, &client_nbr, socket) != SUCCESS)
				continue ;
			if (len != sizeof(t_vector))
				remove_client(clients, &csin, &client_nbr);
			else
				set_player_pos(clients, buffer, &csin);
			send_pos_to_clients(clients, client_nbr, socket);
		}
	}
}

int			main(void)
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
	ft_putstr_fd("wolferver: Server closing...\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
