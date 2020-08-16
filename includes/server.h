/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 11:33:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/16 13:47:23 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "wolfdata.h"
# include <arpa/inet.h>

# define MAX_CLIENTS	16
# define WLF_PORT		4221
# ifndef SRV_BUFF
#  define SRV_BUFF		16
# endif
# define INVALID_SOCKET	-1
# define SOCKET_ERROR	-1
# define PLAYER_POS		1
# define REMOVE_PLAYER	2

typedef struct	s_client
{
	struct sockaddr_in	sin;
	t_vector			player_pos;
	int32_t				sockfd;
	char				player_name[17];
	int8_t				connection_status;
	char				gap_0;
}				t_client;

int8_t			init_socket(int *sockfd);
int8_t			receive(
		int socket, char *buffer, struct sockaddr_in *csin, int *len);
int8_t			is_client_known(
		t_client *clients, struct sockaddr_in *csin, int *nbr, int socket);
void			remove_client(
		t_client *clients, struct sockaddr_in *sin, int *nbr);
void			send_pos_to_clients(
		t_client *clients, int client_nbr, int socket);
int8_t			quit_server(t_client *clients, int client_nbr, int socket);

#endif
