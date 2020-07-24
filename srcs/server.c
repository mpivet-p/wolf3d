/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:16:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/07/24 16:59:27 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putstr_fd("wolf server: bind failure\n");
		close(sockfd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int8_t	receive(int socket, char *buffer, struct sockaddr_in *csin)
{
	size_t	sinsize;
	int		len;

	sinsize = sizeof(*csin);
	if ((*len = recvfrom(socket, buffer, SRV_BUFF
					, 0, (struct sockaddr_in*)sin, &sinsize)) < 0)
	{
		ft_putstr_fd("wolf server: recvfrom error\n", STDERR_FILENO);
		return (FAILURE);
	}
	buffer[*len] = 0;
	return (SUCCESS);
}

static is_client_known(t_client *clients, struct sockaddr_in *csin, int *max, int *nbr)
{
	int	i;

	i = 0;
	while (i < *nbr)
	{
		if (csin->sin_addr.s_addr == clients[i].addr)
			//known host
		i++;
	}
	//unknown host
}

static void	process_data(char *buffer, int len)
{
	ft_putstr("wolf server: new data received\n");
}

static void	run_server(int socket, t_client *clients)
{
	int8_t		client_nbr;
	fd_set		rdfs;
	int8_t		max;
	int			len;
	char		buffer[SRV_BUFF + ];

	while(1)
	{
		FD_ZERO(&rdfs);
		FD_SET(socket, &rdfs);
		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			close_all_connections();
			return (FAILURE);
		}
		if (FD_ISSET(socket, &rdfs))
		{
			receive(socket, buffer, &csin);
			is_client_known(clients, csin, &max, &client_nbr);
			process_data(buffer, &len);
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
