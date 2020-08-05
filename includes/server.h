/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 11:33:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/08/05 17:45:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define MAX_CLIENTS	16
# define WLF_PORT		4221
# ifndef SRV_BUFF
#  define SRV_BUFF		1024
# endif
# define INVALID_SOCKET	-1
# define SOCKET_ERROR	-1
# define PLAYER_POS		1
# define REMOVE_PLAYER	2

# include "wolfdata.h"
# include <arpa/inet.h>

int8_t	init_socket(int *sockfd);

typedef struct	s_client
{
	struct sockaddr_in	sin;
	t_vector			player_pos;
	int32_t				sockfd;
	char				player_name[17];
	int8_t				connection_status;
	char				gap_0;
}				t_client;

#endif
